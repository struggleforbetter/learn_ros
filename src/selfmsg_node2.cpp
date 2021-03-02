#include "ros/ros.h"
#include "beginner_tutorials/name.h"
class NameSub
{
public:
    NameSub(ros::NodeHandle& nh, std::string topic_name,size_t buff_size)
    {
        nh_ = nh;
        topic_name_ = topic_name;
        sub_ = nh_.subscribe(topic_name_,buff_size,&NameSub::callBack,this);
    }
    
private:
    ros::NodeHandle nh_;
    std::string topic_name_;
    ros::Subscriber sub_;
    void callBack(const beginner_tutorials::name::ConstPtr& msg)
    {
        std::cout << "first name: " << msg->first_name << std::endl;
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "selfmsg_sub");
    ros::NodeHandle nh;
    std::string topic = "/my_name";
    NameSub sub(nh,topic,1);
    ros::Rate freq(200);
    while(ros::ok())
    {
      ros::spinOnce();
      freq.sleep();
    }
    return 0;
}