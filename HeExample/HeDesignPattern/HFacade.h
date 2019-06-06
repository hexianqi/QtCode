/***************************************************************************************************
**      2019-05-30  外观模式
**                  https://blog.csdn.net/liang19890820/article/details/70850367
***************************************************************************************************/

#ifndef HFACADE_H
#define HFACADE_H

// 订单团队
class OrderTeam
{
public:
    // 将请求转发给订单团队
    void submitRequest();
    // 检测状态
    bool checkStatus();

private:
    enum States
    {
        Received,       // 收到
        VerifyPayment,  // 确认付款
        ContactVendor,  // 联系供应商
        Complete        // 完成
    };
    int _state = 0;
};

// 供应商
class Vendor
{
public:
    // 将请求转发给供应商
    void submitRequest();
    // 检测状态
    bool checkStatus();

private:
    enum States
    {
        Received,               // 收到
        VerifyInventory,        // 确认库存
        GetItemFromWareHouse,   // 从仓库得到物品
        PackItem,               // 包装
        ContactCourier,         // 联系快递员
        Complete                // 完成
    };
    int _state = 0;
};

// 快递员
class Courier
{
public:
    // 将请求转发给快递员
    void submitRequest();
    // 检测状态
    bool checkStatus();

private:
    enum States
    {
        Received,               // 收到
        VerifyReachbility,      // 验证可达性
        AssignPerson,           // 分配人员
        DispatchPackage,        // 派送包裹
        GetDeliveryConfirmation,// 获取交货确认
        Complete                // 完成
    };
    int _state = 0;
};

// 网购外观
class OnlineShoppingFacade
{
public:
    // 返回跟踪次数
    int followupNum();
    // 提交订单
    void submitRequest();
    // 跟踪订单
    bool checkStatus();

private:
    enum States
    {
        Received,               // 收到
        SubmittedToOrderTeam,   // 提交给订单团队
        SubmittedToVendor,      // 提交给供应商
        SubmittedToCourier      // 提交给快递员
    };

    int _state = 0;  // 订单状态
    int _count = 0;  // 跟踪次数
    OrderTeam _order;
    Vendor _vendor;
    Courier _courier;
};

#endif // HFACADE_H
