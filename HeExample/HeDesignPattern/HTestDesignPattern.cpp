#include "HTestDesignPattern.h"
#include "HDesignPattern.h"
#include "HBuilder.h"
#include "HPrototype.h"
#include "HAdapter.h"
#include "HBridge.h"
#include "HDecorator.h"
#include "HComposite.h"
#include "HFacade.h"
#include "HFlyweight.h"
#include "HProxy.h"
#include "HTemplate.h"
#include "HCommand.h"
#include "HObserver.h"
#include "HMediator.h"
#include "HMemento.h"
#include "HState.h"
#include "HStrategy.h"
#include "HChain.h"
#include "HVisitor.h"
#include "HInterpreter.h"
#include <iostream>
#include <ctime>
#include <windows.h>

void HTestDesignPattern::testBuilder()
{
    auto direcror = new Direcror();
    auto tpBuilder = new ThinkPadBuilder();
    auto yogaBuilder = new YogaBuilder();

    // 组装 ThinkPad、Yoga
    direcror->create(tpBuilder);
    direcror->create(yogaBuilder);

    // 获取组装后的电脑
    auto tpComputer = tpBuilder->getResult();
    auto yogaComputer = yogaBuilder->getResult();

    // 测试输出
    cout << "-----ThinkPad-----" << endl;
    cout << "CPU: " << tpComputer->getCPU() << endl;
    cout << "Mainboard: " << tpComputer->getMainboard() << endl;
    cout << "Ram: " << tpComputer->getRam() << endl;
    cout << "VideoCard: " << tpComputer->getVideoCard() << endl;

    cout << "-----Yoga-----" << endl;
    cout << "CPU: " << yogaComputer->getCPU() << endl;
    cout << "Mainboard: " << yogaComputer->getMainboard() << endl;
    cout << "Ram: " << yogaComputer->getRam() << endl;
    cout << "VideoCard: " << yogaComputer->getVideoCard() << endl;

    SAFE_DELETE(yogaComputer);
    SAFE_DELETE(tpComputer);
    SAFE_DELETE(yogaBuilder);
    SAFE_DELETE(tpBuilder);
    SAFE_DELETE(direcror);
    getchar();
}

void HTestDesignPattern::testPrototype()
{
    // 孙悟空
    auto swk = new SunWuKong("Qi Tian Da Sheng");
    // 克隆猴子猴孙
    auto swk1 = swk->clone();
    auto swk2 = swk->clone();

    swk1->play();
    swk2->play();

    SAFE_DELETE(swk2);
    SAFE_DELETE(swk1);
    SAFE_DELETE(swk);
    getchar();
}

void HTestDesignPattern::testAdapter()
{
    // 创建适配器
    auto *adapter = new PowerAdapter;

    // 充电
    adapter->charge();

    SAFE_DELETE(adapter);
    getchar();
}

void HTestDesignPattern::testBridge()
{
    // 创建电器 - 电灯、风扇
    auto light = new Light;
    auto fan = new Fan;
    // 创建开关 - 拉链式开关、两位开关
    // 将拉链式开关和电灯关联起来，将两位开关和风扇关联起来
    auto pullChain = new PullChainSwitch(light);
    auto twoPosition= new TwoPositionSwitch(fan);

    // 开灯、关灯
    pullChain->on();
    pullChain->off();

    // 打开风扇、关闭风扇
    twoPosition->on();
    twoPosition->off();

    SAFE_DELETE(twoPosition);
    SAFE_DELETE(pullChain);
    SAFE_DELETE(fan);
    SAFE_DELETE(light);
    getchar();
}

void HTestDesignPattern::testDecorator()
{
    /********** 黑咖啡 **********/
    auto *houseBlend = new HouseBlend();
    cout << houseBlend->name() << " : " << houseBlend->cost() << endl;

    // 黑咖啡 + 奶油
    auto *cream = new Cream(houseBlend);
    cout << cream->name() << " : " << cream->cost() << endl;

    // 黑咖啡 + 摩卡
    auto *mocha = new Mocha(houseBlend);
    cout << mocha->name() << " : " << mocha->cost() << endl;

    // 黑咖啡 + 糖浆
    auto *syrup = new Syrup(houseBlend);
    cout << syrup->name() << " : " << syrup->cost() << endl;

    /********** 深度烘培咖啡豆 **********/
    auto *darkRoast = new DarkRoast();
    cout << darkRoast->name() << " : " << darkRoast->cost() << endl;

    // 深度烘培咖啡豆 + 奶油
    auto *creamDR = new Cream(darkRoast);
    cout << creamDR->name() << " : " << creamDR->cost() << endl;

    // 深度烘培咖啡豆 + 奶油 + 摩卡
    auto *creamMocha = new Mocha(creamDR);
    cout << creamMocha->name() << " : " << creamMocha->cost() << endl;

    // 深度烘培咖啡豆 + 奶油 + 摩卡 + 糖浆
    auto *creamMochaSyrup = new Syrup(creamMocha);
    cout << creamMocha->name() << " : " << creamMocha->cost() << endl;

    SAFE_DELETE(creamMochaSyrup);
    SAFE_DELETE(creamMocha);
    SAFE_DELETE(creamDR);
    SAFE_DELETE(darkRoast);
    SAFE_DELETE(syrup);
    SAFE_DELETE(mocha);
    SAFE_DELETE(cream);
    SAFE_DELETE(houseBlend);
    getchar();
}

void HTestDesignPattern::testComposite()
{
    // 创建一个树形结构
    // 创建根节点
    auto root = new TransparentComposite("江湖公司（任我行）");

    // 创建分支1
    auto depart1 = new TransparentComposite("日月神教（东方不败）");
    depart1->add(new TransparentLeaf("光明左使（向问天）"));
    depart1->add(new TransparentLeaf("光明右使（曲洋）"));
    root->add(depart1);
    // 创建分支2
    auto depart2 = new TransparentComposite("五岳剑派（左冷蝉）");
    depart2->add(new TransparentLeaf("嵩山（左冷蝉）"));
    depart2->add(new TransparentLeaf("衡山（莫大）"));
    depart2->add(new TransparentLeaf("华山（岳不群）"));
    depart2->add(new TransparentLeaf("泰山（天门道长）"));
    depart2->add(new TransparentLeaf("恒山（定闲师太）"));
    root->add(depart2);

    // 添加和删除叶子
    root->add(new TransparentLeaf("少林（方证大师）"));
    root->add(new TransparentLeaf("武当（冲虚道长）"));
    auto leaf = new TransparentLeaf("青城（余沧海）");
    root->add(leaf);
    // 小丑，直接裁掉
    root->remove(leaf);

    // 递归地显示组织架构
    root->operation(1);

    // 删除分配的内存
    SAFE_DELETE(root);
    getchar();
}

void HTestDesignPattern::testFacade()
{
    OnlineShoppingFacade facade;

    // 提交订单
    facade.submitRequest();
    // 跟踪订单，直到订单完成
    while (!facade.checkStatus());

    cout << "********** 订单完成，跟踪次数：" << facade.followupNum() << " **********" << endl;
    getchar();
}

void HTestDesignPattern::testFlyweight()
{
    srand((unsigned)time(NULL));

    int playerLen;
    int weaponsLen;
    GET_ARRAY_LEN(__playerType, playerLen);
    GET_ARRAY_LEN(__weapons, weaponsLen);

    // 假设，游戏中有十位玩家
    for (int i = 0; i < 10; i++)
    {
        // 获取随机玩家和武器
        int typeIndex = rand() % playerLen;
        int weaponIndex = rand() % weaponsLen;
        auto type = __playerType[typeIndex];
        auto weapon = __weapons[weaponIndex];
        // 获取玩家
        auto p = PlayerFactory::getPlayer(type);
        // 从武器库中随机分配武器
        p->assignWeapon(weapon);
        // 派玩家去执行任务
        p->mission();
    }
    getchar();
}

void HTestDesignPattern::testProxy()
{
    auto proxy = new Proxy();
    proxy->recharge(20);
    proxy->recharge(100);

    SAFE_DELETE(proxy);
    getchar();
}

void HTestDesignPattern::testTemplate()
{
    auto alibaba = new Alibaba();
    alibaba->recruit();
    auto tencent = new Tencent();
    tencent->recruit();

    SAFE_DELETE(tencent);
    SAFE_DELETE(alibaba);
    getchar();
}

void HTestDesignPattern::testCommand()
{
    auto rev = new Reciever();
    auto cmd1 = new TakeCommand(rev);
    auto cmd2 = new PayCommand(rev);
    Invoker inv;
    inv.addCmd(cmd1);
    inv.addCmd(cmd2);
    inv.notify();

    SAFE_DELETE(cmd1);
    SAFE_DELETE(cmd2);
    SAFE_DELETE(rev);
    getchar();
}

void HTestDesignPattern::testObserver()
{
    // 创建主题、观察者
    auto subject = new ConcreteSubject();
    auto observer1 = new ConcreteObserver("Jack Ma");
    auto observer2 = new ConcreteObserver("Pony");

    // 注册观察者
    subject->attach(observer1);
    subject->attach(observer2);

    // 更改价格，并通知观察者
    subject->setPrice(12.5);
    subject->notify();

    // 注销观察者
    subject->detach(observer2);
    // 再次更改状态，并通知观察者
    subject->setPrice(15.0);
    subject->notify();

    SAFE_DELETE(observer1);
    SAFE_DELETE(observer2);
    SAFE_DELETE(subject);
    getchar();
}

void HTestDesignPattern::testMediator()
{
    // 房东
    auto landlord = new ConcreteColleague("Tom");
    // 租客
    auto jerry = new ConcreteColleague("Jerry");
    auto tuffy = new ConcreteColleague("Tuffy");
    // 中介者 - 添加租客
    ConcreteMediator mediator;
    mediator.registerColleague(jerry);
    mediator.registerColleague(tuffy);

    // 房东通过中介将消息发送出去
    landlord->sendMessage(mediator, "Xi'erqi, two bedroom house, 6000/month.");

    SAFE_DELETE(jerry);
    SAFE_DELETE(tuffy);
    getchar();
}

void HTestDesignPattern::testMemento()
{
    auto life = new Life();
    auto box = new PandoraBox(life);
    // 设置并保存一个历史时间
    life->setDateTime("2000/10/01 00:00:00");
    box->save();
    // 设置并保存一个历史时间
    life->setDateTime("2010/10/01 00:00:00");
    box->save();
    // 设置一个历史时间
    life->setDateTime("2018/10/01 00:00:00");
    // 穿越
    box->undo();
    cout << "Actual date time is " << life->getDateTime() << endl;
    // 再次穿越
    box->undo();
    cout << "Actual date time is " << life->getDateTime() << endl;

    SAFE_DELETE(life);
    SAFE_DELETE(box);
    getchar();
}

void HTestDesignPattern::testState()
{
    enum TLState { Red, Green, Yellow };

    TrafficLights tl;
    TLState state = Red;    // 初始状态为红灯
    int i = 0;              // 总次数
    int seconds;            // 秒数

    while (true)
    {
        // 表示一个完整的状态流（红灯->绿灯->黄灯）已经完成
        if (i % 3 == 0)
            cout << "**********" << "Session " << ((i + 1) / 3) + 1 << "**********" << endl;

        // 根据当前状态来设置持续时间，红灯（6秒）、绿灯（4秒）、黄灯（2秒）
        if (state == Red)
        {
            seconds = 6;
            state = Green;
        }
        else if (state == Green)
        {
            seconds = 4;
            state = Yellow;
        }
        else if (state == Yellow)
        {
            seconds = 2;
            state = Red;
        }
        // 休眠
        Sleep(seconds * 1000);
        tl.request();
        i++;
    }
}

void HTestDesignPattern::testStrategy()
{
    // 策略之间可以相互替换
    auto bike = new BikeStrategy();
    auto car = new CarStrategy();
    auto train = new TrainStrategy();

    auto bikeContext = new Context(bike);
    auto carContext = new Context(car);
    auto trainContext = new Context(train);

    bikeContext->travel();
    carContext->travel();
    trainContext->travel();

    SAFE_DELETE(bike);
    SAFE_DELETE(car);
    SAFE_DELETE(train);
    SAFE_DELETE(bikeContext);
    SAFE_DELETE(carContext);
    SAFE_DELETE(trainContext);
    getchar();
}

void HTestDesignPattern::testChain()
{
    auto manager = new Manager();
    auto director = new Director();
    auto ceo = new CEO();

    // 职责链：经理 -> 总监 -> 总裁
    manager->setSuccessor(director);
    director->setSuccessor(ceo);
    manager->handleRequest(1);
    manager->handleRequest(2);
    manager->handleRequest(5);
    manager->handleRequest(10);
    SAFE_DELETE(manager);
    SAFE_DELETE(director);
    SAFE_DELETE(ceo);
    getchar();
}

void HTestDesignPattern::testVisitor()
{
    auto city = new City();
    // 景点 - 钟楼、兵马俑
    auto bellTower = new BellTower();
    auto warriors = new TerracottaWarriors();
    // 访问者 - 游客、清洁工
    auto tourist = new Tourist();
    auto cleaner = new Cleaner();

    // 添加景点
    city->attach(bellTower);
    city->attach(warriors);
    // 接受访问
    city->accept(tourist);
    city->accept(cleaner);

    SAFE_DELETE(cleaner);
    SAFE_DELETE(tourist);
    SAFE_DELETE(warriors);
    SAFE_DELETE(bellTower);
    SAFE_DELETE(city);
    getchar();
}

/*************************
 * 运算结果为：a+b-c = 80
 * ~VarExpression()
 * ~VarExpression()
 * ~AddExpression()
 * ~VarExpression()
 * ~SubExpression()
*************************/
void HTestDesignPattern::testInterpreter()
{
    // 为简化处理，这里必须是合法的表达式
    string expStr = "a+b-c";

    // 相当于Interpreter模式中的Context
    map<string, int> var;
    var["a"] = 100;
    var["b"] = 20;
    var["c"] = 40;
    Calculator cal(expStr);
    cout <<"运算结果为：" << expStr << " = " << cal.run(var) << endl;
    getchar();
}

/************************************************************************
 * 输出结果：
 * 输入指令: up move 5 and down run 10 and left move 5
 * 移动结果：向上移动5再向下快速移动10再向左移动5
 * 输入指令: right run 20 and down move 10 and left run 40 and up run 10
 * 移动结果：向右快速移动20再向下移动10再向左快速移动40再向上快速移动10
*************************************************************************/
void HTestDesignPattern::testInterpreter2()
{
    string instruction = "up move 5 and down run 10 and left move 5";

    InstructionHandler handler;
    handler.handle(instruction);
    cout <<"输入指令: " << instruction <<endl;
    cout <<"移动结果：" << handler.output() << endl;

    instruction = "right run 20 and down move 10 and left run 40 and up run 10";
    handler.handle(instruction);
    cout <<"输入指令: " <<instruction <<endl;
    cout <<"移动结果：" << handler.output() << endl;
    getchar();
}
