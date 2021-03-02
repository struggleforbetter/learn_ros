#include "ros/ros.h"
#include "std_msgs/String.h"

class multiReceiver
{
public:
	multiReceiver()
	{	
		sub = nh.subscribe("chatter1", 1, &multiReceiver::chatterCallback1,this);
		sub2 = nh.subscribe("chatter2", 1, &multiReceiver::chatterCallback2,this);
	}
	void chatterCallback1(const std_msgs::String::ConstPtr& msg);
	void chatterCallback2(const std_msgs::String::ConstPtr& msg);

private:
	ros::NodeHandle nh;
	ros::Subscriber sub;
	ros::Subscriber sub2;
  
};
class Sub1
{
  public:
    Sub1(ros::NodeHandle& nh, std::string topic_name, size_t buff_size)
    {
      nh_ = nh;
      subscriber_ = nh_.subscribe(topic_name,buff_size,&Sub1::msg_callback,this);
    }
    Sub1() = default;
  private:
    void msg_callback(const std_msgs::String::ConstPtr& msg)
    {
      ROS_INFO("sub1: [%s]", msg->data.c_str());
    }

  private: 
    ros::NodeHandle nh_;
    ros::Subscriber subscriber_;
};

class Sub2
{
  public:
    Sub2(ros::NodeHandle& nh, std::string topic_name, size_t buff_size)
    {
      nh_ = nh;
      subscriber_ = nh_.subscribe(topic_name,buff_size,&Sub2::msg_callback,this);
    }
    Sub2() = default;
  private:
    void msg_callback(const std_msgs::String::ConstPtr& msg)
    {
      ROS_INFO("sub2: [%s]", msg->data.c_str());
      sleep(5);
    }

  private: 
    ros::NodeHandle nh_;
    ros::Subscriber subscriber_;
};

void multiReceiver::chatterCallback1(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  // ros::Rate loop_rate(0.5);//block chatterCallback2()
  // loop_rate.sleep();
  sleep(5);
}

void multiReceiver::chatterCallback2(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}
  

// int main(int argc, char **argv)
// {

//     ros::init(argc, argv, "multi_sub");
//     ros::NodeHandle nh;
//     ros::AsyncSpinner spinner(2);
//     spinner.start();
//     multiReceiver recOb;
//     ros::Rate freq(200);
//     while(ros::ok())
//     {
//       freq.sleep();
//     }
    
//     // ros::spin();

//     return 0;
// }

int main(int argc, char **argv)
{

    ros::init(argc, argv, "multi_sub");
    ros::NodeHandle nh;
    // ros::AsyncSpinner spinner(2);
    // spinner.start();
    Sub1 sub1(nh,"chatter1",100);
    Sub2 sub2(nh,"chatter2",1);

    ros::Rate freq(200);
    while(ros::ok())
    {
      ros::spinOnce();
      freq.sleep();
    }
    
    // ros::spin();

    return 0;
}
