#include "HFacade.h"
#include <iostream>
#include <windows.h>

using namespace std;

const string __stateToStrCourier[] = { "收到", "验证可达性", "分配人员", "派送包裹", "获取交货确认", "完成" };
const string __stateToStrVendor[] = { "收到", "确认库存", "从仓库得到物品", "包装", "联系快递员", "完成" };
const string __stateToStrOrderTeam[] = { "收到", "确认付款", "联系供应商", "完成" };
const int waitTime = 300;

void OrderTeam::submitRequest()
{
    _state = 0;
}

bool OrderTeam::checkStatus()
{
    cout << "订单团队 - 当前状态：" << __stateToStrOrderTeam[_state] << endl;
    Sleep(waitTime);
    _state++;
    return (_state == Complete);
}

void Vendor::submitRequest()
{
    _state = 0;
}

bool Vendor::checkStatus()
{
    cout << "供应商 - 当前状态：" << __stateToStrVendor[_state] << endl;
    Sleep(waitTime);
    _state++;
    return (_state == Complete);
}

void Courier::submitRequest()
{
    _state = 0;
}

bool Courier::checkStatus()
{
    cout << "快递员 - 当前状态：" << __stateToStrCourier[_state] << endl;
    Sleep(waitTime);
    _state++;
    return (_state == Complete);
}

int OnlineShoppingFacade::followupNum()
{
    return _count;
}

void OnlineShoppingFacade::submitRequest()
{
    _state = 0;
}

bool OnlineShoppingFacade::checkStatus()
{
    // 收到订单请求
    switch (_state)
    {
    case Received:
        _state++;
        // 将请求转发给订单团队
        _order.submitRequest();
        cout << "********** 提交给订单团队，跟踪次数：" << _count << " **********" << endl;
        break;
    case SubmittedToOrderTeam:
        // 如果订单团队完成验证，则向供应商发出请求
        if (_order.checkStatus())
        {
            _state++;
            _vendor.submitRequest();
            cout << "********** 提交给供应商，跟踪次数：" << _count << " **********" << endl;
        }
        break;
    case SubmittedToVendor:
        // 如果供应商已将包裹打包，将其转发给快递员
        if (_vendor.checkStatus())
        {
            _state++;
            _courier.submitRequest();
            cout << "********** 提交给快递员，跟踪次数：" << _count << " **********" << endl;
        }
        break;
    case SubmittedToCourier:
        // 如果包裹交付，订单完成
        if (_courier.checkStatus())
            return true;
    default:
        break;
    }
    _count++;
    // 订单未完成
    return false;
}
