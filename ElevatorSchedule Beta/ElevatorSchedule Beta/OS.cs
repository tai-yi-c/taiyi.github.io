using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
namespace ElevatorSchedule_Beta
{
    class OS
    {
        //系统控制部件
        public int TimeSlice=1000;
        //就绪队列 规模小，不做结构体
        private TCB[] ReadyTCB = new TCB[5];
        Queue<task> WaitTask=new Queue<task>();
        int WaitCnt = 0;
        public Elevator[] InForm = new Elevator[5];
        private ElevatorSchedule OutForm = new ElevatorSchedule();
        //初始化函数
        public OS(Elevator[] ElevatorForm, ElevatorSchedule thisOutForm) {
            //TCB初始化
            InForm = ElevatorForm;
            OutForm = thisOutForm;
            for (int i = 0; i < 5; i++)
            {
                //修改一下窗口的拥有者
                ReadyTCB[i] = new TCB(i,OutForm);
                InForm[i].ithelevator = ReadyTCB[i];
                
                ReadyTCB[i].InForm = InForm[i];
            }
        }
        //中断类型，先不用
        private void Interupt() { }
        //很有可能不是这样写的
        public void ReDispatch() { 
            
            for(int i = 0; i < WaitCnt; i++)
            {
                
                task thisTask = WaitTask.Dequeue();
                WaitCnt--;
                Dispatch(thisTask.floor, thisTask.order);
            }
        }
        //暂时接受外部调用的函数
        public void Dispatch(int floor,Order order) {
            
            int flag = 1;
            if (order == Order.up)
            {
                 //算优先级
                 for(int i = 0; i < 5; i++)
                {
                    if(ReadyTCB[i].status==Status.up)
                    {
                        if(ReadyTCB[i].begin<=floor && ReadyTCB[i].end >= floor)
                        {
                            if (floor - ReadyTCB[i].floor > 0) ReadyTCB[i].prior = floor - ReadyTCB[i].floor;
                            else ReadyTCB[i].prior = ReadyTCB[i].floor - floor;

                            flag = 0;
                        }
                    }else if(ReadyTCB[i].status == Status.free)
                    {
                        if (floor - ReadyTCB[i].floor > 0) ReadyTCB[i].prior = floor - ReadyTCB[i].floor;
                        else ReadyTCB[i].prior = ReadyTCB[i].floor - floor;
                        flag = 0;
                    }
                }
                 //如果没有合适的电梯
                if (flag == 1)
                {
                    task thisTask = new task();
                    thisTask.floor = floor;
                    thisTask.order = order;
                    WaitTask.Enqueue(thisTask);
                    WaitCnt++;
                }
                else
                {   //如果有合适的电梯
                    int idx = 0;//最高优先级的电梯
                    for (int i = 0; i < 5; i++)
                    {
                        if (ReadyTCB[i].status == Status.up || ReadyTCB[i].status == Status.free)
                        {
                            if (ReadyTCB[i].prior < ReadyTCB[idx].prior) idx = i;
                        }
                    }
                    //分配给idx的电梯
                    ReadyTCB[idx].ReceiveTask(floor, order);
                }
            }
            else
            {
                for (int i = 0; i < 5; i++)
                {
                    if (ReadyTCB[i].status == Status.down)
                    {
                        if (ReadyTCB[i].begin >=floor && ReadyTCB[i].end <= floor)
                        {
                            if (floor - ReadyTCB[i].floor > 0) ReadyTCB[i].prior = floor - ReadyTCB[i].floor;
                            else ReadyTCB[i].prior = ReadyTCB[i].floor - floor;
                            flag = 0;
                        }
                    }else if(ReadyTCB[i].status == Status.free)
                    {
                        if (floor - ReadyTCB[i].floor > 0) ReadyTCB[i].prior = floor - ReadyTCB[i].floor;
                        else ReadyTCB[i].prior = ReadyTCB[i].floor - floor;
                        flag = 0;
                    }
                }
                if (flag == 1)
                {
                    task thisTask = new task();
                    thisTask.floor = floor;
                    thisTask.order = order;
                    WaitTask.Enqueue(thisTask);
                    WaitCnt++;
                }
                else
                {
                    int idx = 0;//最高优先级的电梯
                    for (int i = 0; i < 5; i++)
                    {
                        if (ReadyTCB[i].status == Status.down || ReadyTCB[i].status == Status.free)
                        {
                            if (ReadyTCB[i].prior < ReadyTCB[idx].prior) idx = i;
                        }
                    }
                    ReadyTCB[idx].ReceiveTask(floor, order);
                }
            }
            return;
        }
        public void Schedule(int ith) 
        {
            
            ReadyTCB[ith-1].Execute();
        }
    }
}
