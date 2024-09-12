#include "ThreadAsync.h"
#include <iostream>

// һ����ʱ�ĺ���
int longTask(int num)
{
    std::cout << __FUNCTION__ << ":start run thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5)); // ģ���ʱ����
    std::cout << __FUNCTION__ << ":end thread" << std::endl;
    return num * 2;
}

int testThreadAsync()
{
    // ʹ��std::async�����첽����
    std::future<int> result = std::async(std::launch::async, longTask, 10);
    std::cout << __FILE__ << std::endl;
    // �����������������������
    std::cout << __FUNCTION__ << ":Deal other ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // ģ���ʱ����
    // ��ȡ�첽����Ľ��
    std::cout << __FUNCTION__ << ":Wiat result" << std::endl;
    int value = result.get();  // ������ֱ���������

    std::cout << __FUNCTION__ << ":get Result: " << value << std::endl;

    return 0;
}
