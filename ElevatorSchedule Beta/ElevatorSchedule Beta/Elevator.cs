using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ElevatorSchedule_Beta
{
    public partial class Elevator : Form
    {
        //楼层按钮，0节点空置
        public Button[] button_floor = new Button[20];
        public TCB ithelevator;
        public Elevator()
        {
            InitializeComponent();
            for (int i = 0; i < 20; i++)
            {
                button_floor[i] = (Button)this.Controls.Find("button" + Convert.ToString(i + 1), true)[0];
                button_floor[i].Name = Convert.ToString(i + 1);
                button_floor[i].BackColor = Color.Gray;
                button_floor[i].Click += new EventHandler(button_floor_Click);

            }
        }
        //需要初始化按钮
        private void Elevator_Load(object sender, EventArgs e)
        {
            
        }
        public void button_floor_Click(object sender, EventArgs e)
        {
            
            Button btn = (Button)sender;
            int floor = int.Parse(btn.Name);
            if (floor == ithelevator.floor)
            {
                MessageBox.Show("就在这层");
                return;
            }
            
            btn.BackColor = Color.Yellow;//变颜色
            btn.Enabled = false;
            ithelevator.ReceiveFloor(floor);
        }
        //按键更新以及显示器更新
        public void Refresh(int floor,Status status) {
            
            button_floor[floor - 1].BackColor = Color.Gray;
            //button_floor[floor - 1].Enabled = true;//只有全部刷新的时候可以更新按键
            button21.Text = Convert.ToString(floor) + "F";
            Execute(status);
            //if (status == Status.up) label2.Text = "运行状态：电梯上行";
            //else if (status == Status.down) label2.Text = "运行状态：电梯下行";
            //else label2.Text = "运行状态：电梯就绪";
        }
        public void Fresh()
        {
            for (int i = 0; i < 20; i++)
            {
                button_floor[i].BackColor = Color.Gray;
                button_floor[i].Enabled = true;
            }
        }
        //运行的过程之中，把运行方向之后的按钮全部阻塞掉
        public void Move(int floor,Status status)
        {
            //暂时不能按本层
            if (status == Status.up)
            {
                for (int i = 0; i < 20; i++)
                {
                    if (i + 1 <= floor)
                    {
                        button_floor[i].Enabled = false;
                    }
                }
            }
            else if (status == Status.down)
            {
                for (int i = 0; i < 20; i++)
                {
                    if (i + 1 >= floor)
                    {
                        button_floor[i].Enabled = false;//不能点击
                    }
                }
            }
           
            
        }
        //状态倒转
        public void StatusChange(int floor, Status status)
        {
            Pause(status);
            Fresh();//先全部恢复
            Move(floor,status);//然后再把这一层之后的按钮全部阻塞
        }
        public void Execute(Status status)
        {
            if (status == Status.up) label2.Text = "运行状态：电梯上行";
            else if (status == Status.down) label2.Text = "运行状态：电梯下行";
            else label2.Text = "运行状态：电梯就绪";
        }
        public void Pause(Status status)
        {
            if (status == Status.up) label2.Text = "运行状态：电梯等待，当前指令上行";
            else if (status == Status.down) label2.Text = "运行状态：电梯等待，当前指令下行";
            else label2.Text = "运行状态：电梯就绪";
        }

        private void button22_Click(object sender, EventArgs e)
        {
            ithelevator.Alert(0);
        }

        private void button23_Click(object sender, EventArgs e)
        {
            ithelevator.Alert(1);
        }

        private void button24_Click(object sender, EventArgs e)
        {
            if (ithelevator.status != Status.free)
            {
                MessageBox.Show("危险行为，请等电梯停靠");
                return;
            }
            ithelevator.OpenDoor();
        }

        private void button25_Click(object sender, EventArgs e)
        {
            if (ithelevator.status != Status.free)
            {
                MessageBox.Show("危险行为，请等电梯停靠");
                return;
            }
            ithelevator.CloseDoor();
        }
    }
}
