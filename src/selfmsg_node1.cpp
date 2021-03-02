#include "ros/ros.h"
#include "beginner_tutorials/name.h"
class NamePub
{
public:
    NamePub(ros::NodeHandle& nh, std::string topic_name,size_t buff_size)
    {
        nh_ = nh;
        topic_name_ = topic_name;
        publisher_ = nh_.advertise<beginner_tutorials::name>(topic_name_,buff_size);
    }
    void pubMsg(const beginner_tutorials::name& msg)
    {
        publisher_.publish(msg);
    }
private:
    ros::NodeHandle nh_;
    std::string topic_name_;
    ros::Publisher publisher_;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "selfmsg_pub");
    ros::NodeHandle nh;
    std::string topic = "/my_name";
    NamePub pub(nh,topic,1);
    beginner_tutorials::name msg;
    msg.header.stamp = ros::Time::now();
    msg.first_name = "Jim";
    msg.last_name = "Green";
    msg.age = 8;
    msg.score = 90;
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        pub.pubMsg(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}