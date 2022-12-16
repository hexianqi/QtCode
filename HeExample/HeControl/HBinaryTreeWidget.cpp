#include "HBinaryTreeWidget_p.h"
#include "HDrawHelper.h"
#include <QtCore/QStack>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

enum class TreeType // 当前字符处理的类型
{
    leftChild,
    rightChild,
    noChild
};

// 创建二叉树
void createBinaryTree(HBinaryTreeNode * & root, QString text)
{
    TreeType treeType = TreeType::noChild;
    HBinaryTreeNode *node = nullptr;
    QStack<HBinaryTreeNode *> stack;
    root = nullptr;
    for (const auto &element : qAsConst(text))
    {
        if (element == '(') // 表示一棵左子树的开始,即将前面刚创建的结点作为双亲结点进栈
        {
            stack.push(node);
            treeType = TreeType::leftChild;
        }
        else if (element == ')') // 表示一棵子树的结束
        {
            stack.pop();
        }
        else if (element == ',') // 表示一棵右子树的开始
        {
            treeType = TreeType::rightChild;
        }
        else // 字母，说明应该创建一个结点
        {
            node = new HBinaryTreeNode;
            node->data = element;

            if (!root)
                root = node;
            else
            {
                switch (treeType)
                {
                case TreeType::leftChild:
                    stack.top()->lchild = node;
                    break;
                case TreeType::rightChild:
                    stack.top()->rchild = node;
                    break;
                case TreeType::noChild:
                    break;
                }
            }
        }
    }
}

// 递归销毁二叉树
void destroyBinaryTree(HBinaryTreeNode * & node)
{
    if (!node)
        return;
    destroyBinaryTree(node->lchild);
    destroyBinaryTree(node->rchild);
    delete node;
    node = nullptr;
}

void drawNode(QPainter *painter, HBinaryTreeNode * node, QPoint center)
{
    auto offset = QPoint(20, 20);
    auto rect = QRect(center - offset, center + offset);

    if (node->lchild)
    {
        painter->drawLine(rect.center(), center + QPoint(-60, 60));
        drawNode(painter, node->lchild, center + QPoint(-60, 60));
    }
    if (node->rchild)
    {
        painter->drawLine(rect.center(), center + QPoint(60, 60));
        drawNode(painter, node->rchild, center + QPoint(60, 60));
    }

    painter->save();
    painter->setBrush(HDrawHelper::randomColor());
    painter->setPen(QPen(Qt::white, 2));
    painter->drawEllipse(rect);
    painter->drawText(rect, Qt::AlignCenter, node->data);
    painter->restore();
}

HBinaryTreeWidget::HBinaryTreeWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HBinaryTreeWidgetPrivate)
{
    setBinaryTree("A(B(D(M(N,),G(W(,H),))),C(E,F(P,Z(,K(Y,)))))");
}

HBinaryTreeWidget::~HBinaryTreeWidget()
{
    destroyBinaryTree(d_ptr->root);
}

void HBinaryTreeWidget::setBinaryTree(const QString &text)
{
    destroyBinaryTree(d_ptr->root);
    createBinaryTree(d_ptr->root, text);
}

void HBinaryTreeWidget::paintEvent(QPaintEvent *)
{
    static QFont font{"微软雅黑",18};
    QPainter painter(this);
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing,true);
    drawNode(&painter, d_ptr->root, QPoint(width() / 2, 40));
}

HE_END_NAMESPACE

