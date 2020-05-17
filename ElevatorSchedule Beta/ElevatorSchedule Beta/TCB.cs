using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ElevatorSchedule_Beta
{
    //TCB就是elevator类，代码段，数据段 直接写在里面了，不好模拟段指针
    //后面考虑拆开成两个类
    public class TCB
    {
        //琐碎的信息
        private int Tid;
        public int prior;
        public int begin;
        public int end;
        private int FreeOrder=0;
        public int floor=1;
        public Status status;
        //private Order order;
        //整体任务
        private int[] TaskList = new int[21];//0节点空置
        //外部任务
        private Order[] OutTask = new Order[21];//0节点空置
        public ElevatorSchedule OutForm;
        public Elevator InForm;

        public TCB(int id, ElevatorSchedule form1) {
            Tid = id;
            prior = 1000;
            begin = 1;
            end = 1;
            //floor = 1;
            status = Status.free;
            //order = Order.free;
            for(int i = 0; i < 21; i++)
            {
                TaskList[i] = 0;
                OutTask[i] = Order.free;
            }
            OutForm = form1;
            //InForm = form2;
        }
        //外部任务
        public void ReceiveTask(int thisfloor,Order thisorder) {
            prior = 1000;//重置优先级
            TaskList[thisfloor] = 1;
            OutTask[thisfloor] = thisorder;
            begin = floor;
            if (status == Status.free)
            {
                if (thisfloor > floor)
                {
                    status = Status.up;
                    end = thisfloor;
                }
                else if (thisfloor < floor)
                {
                    status = Status.down;
                    end = thisfloor;
                }
                else FinishTask(); //同层任务直接完成
            }
            else
            { 
                //否则必定是同向的任务，一定在界限之内，不用更新范围
                //有两种可能，一是不在同层，二是在同层
                if(thisfloor==floor) FinishTask();//同层任务直接完成
            }
           
            //如果是需要转向的电梯(比如电梯在一楼，第三楼有人按下键)，不允许按更高层的楼层
            //更新按键是什么时候？
        }
        //只要还有任务就是true 没有任务是false
        public bool ExistTask() 
        {
            if (begin == end) return false;
            else return true;
        }
        //小心，反向运行的情况
        //注意电梯与运行画面的步调不一致
        public void ReceiveFloor(int dfloor) {
            begin = floor;//冗余设计，避免出错
            TaskList[dfloor] = 1;
            if (status == Status.free)
            {
                end = dfloor;
                if (dfloor > floor) status = Status.up;
                else if (dfloor < floor) status = Status.down;
                else FinishTask();//其实不可能点击同层---有可能点击同层，异步运行的
            }
            else
            {
                //有可能会存在点击反方向的按钮的情况
                //不允许点击同层按钮,被关闭了
                if (status == Status.up) 
                {
                    if(dfloor>end) end = dfloor;
                }
                else
                {
                    if (dfloor < end) end = dfloor;
                }
            }

        }
        public void Execute() {
            //暂时一个时钟只执行一下
            CloseDoor();
            if (ExistTask())
            {
                
                if (status == Status.up)
                {
                    floor += 1;begin += 1;
                    OutForm.Move(Tid,floor,status);//修改位置
                    OutForm.Refresh(Tid, floor, status);
                    InForm.Move(floor,status);//停用一些按钮
                    InForm.Refresh(floor,status);
                    if (CheckFloor()) FinishTask();
                }
                else if(status == Status.down)
                {
                    floor -= 1;begin -= 1;
                    OutForm.Move(Tid, floor, status);//等待修改
                    OutForm.Refresh(Tid, floor, status);
                    InForm.Move(floor, status);
                    InForm.Refresh(floor, status);
                    if (CheckFloor()) FinishTask();
                }
            }
            else
            {
                //无指令次数到达10次就恢复到就绪状态 停了10秒
                FreeOrder += 1;
                if (FreeOrder >= 10)
                {
                    prior = 1000;
                    status = Status.free;
                    InForm.Fresh();
                    begin = floor; end = floor;
                    FreeOrder = 0;
                    InForm.Pause(status);
                    OutForm.Refresh(Tid, floor, status);
                }
            }
        }
        //如果是任务楼层就完成任务
        private bool CheckFloor()
        {
            if (TaskList[floor] > 0) return true;
            else return false;
        }

        private void FinishTask()//finish之后等待下一次时钟中断才会影响楼层变化
        {
            OpenDoor();          
            //外部命令 其中存在同层任务
            if (OutTask[floor] != Order.free)
            {
                //检测电梯状态与命令方向是否相反
                //如果相反，转换文字
                //有没有可能电梯就绪，但是有命令，这个地方有可能来自于外部同层命令
                if(status==Status.up && OutTask[floor] == Order.down)
                {
                    //转换为下行
                    status = Status.down;
                    InForm.StatusChange(floor, status);//有效按键倒转
                    end = floor;
                    for (int i = floor; i <= 20; i++)//更高层的任务注销掉
                    {
                        if (TaskList[i] != 0)
                        {
                            TaskList[i] = 0;
                            InForm.Refresh(i, status);

                        }
                    }
                }
                else if(status == Status.down && OutTask[floor] == Order.up)
                {
                    //转换为上行
                    status = Status.up;
                    InForm.StatusChange(floor, status);
                    end = floor;
                    for(int i = floor; i >= 1; i--)
                    {
                        if (TaskList[i] != 0)
                        {
                            TaskList[i] = 0;
                            InForm.Refresh(i,status);
                        }
                    }
                }
                else//同向，或者没有方向
                {
                    //如果电梯是暂停的输出就绪---并且要转换电梯状态
                    //如果同向，输出方向----转不转换都可以，运行函数已经阻塞按钮
                    InForm.Pause(status);
                   
                }
                //强制转换电梯状态,是对上面else的补充
                if (OutTask[floor] == Order.up) status = Status.up;
                else if(OutTask[floor] == Order.down) status = Status.down;

                //同层且电梯就绪状态的命令，
                InForm.Move(floor, status);//冗余化执行，把此方向之后的按键全部阻塞

                OutTask[floor] = Order.free;//删除命令
                //更新外部按钮,显示屏和标签
                OutForm.Refresh(Tid,floor, status);
            }
            OutForm.Pause(Tid, status);
            //内部命令 不在这里执行
            //如果任务列表完成
            if (!ExistTask())
            {
                //不存在任务了
                if (status == Status.free)
                {
                    //完全刷新
                    InForm.Fresh();
                    begin = floor; end = floor;
                }
                
            }
            TaskList[floor] = 0;//消除内部任务
        }
        //报警
        public void OpenDoor()
        {
            Button btn1 = (Button)OutForm.Controls.Find("button" + Convert.ToString(Tid + 1), true)[0];
            btn1.Text = "开门";
        }
        public void CloseDoor()
        {
            Button btn1 = (Button)OutForm.Controls.Find("button" + Convert.ToString(Tid + 1), true)[0];
            btn1.Text = "电梯" + Convert.ToString(Tid + 1);
        }
        public void Alert(int sig)
        {
            OutForm.Alert(Tid,sig);
        }

    }
}
