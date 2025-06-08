#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include "LifeWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建主窗口
    QMainWindow window;
    window.setWindowTitle("细胞生命游戏");

    // 创建主控件
    QWidget *centralWidget = new QWidget(&window);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // 创建游戏区域
    LifeWidget *lifeWidget = new LifeWidget;

    // 创建控制面板
    QWidget *controlPanel = new QWidget;
    QVBoxLayout *controls = new QVBoxLayout(controlPanel);

    // 控制按钮
    QPushButton *startButton = new QPushButton("开始");
    QObject::connect(startButton, &QPushButton::clicked,
                     lifeWidget, &LifeWidget::toggleSimulation);

    QPushButton *clearButton = new QPushButton("清空");
    QObject::connect(clearButton, &QPushButton::clicked,
                     lifeWidget, &LifeWidget::clear);

    QPushButton *randomButton = new QPushButton("随机");
    QObject::connect(randomButton, &QPushButton::clicked,
                     lifeWidget, &LifeWidget::randomize);

    // 速度控制
    QSlider *speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setRange(50, 2000);
    speedSlider->setValue(200);
    QObject::connect(speedSlider, &QSlider::valueChanged,
                     lifeWidget, &LifeWidget::setInterval);

    // 布局控件
    controls->addWidget(startButton);
    controls->addWidget(clearButton);
    controls->addWidget(randomButton);
    controls->addWidget(new QLabel("速度:"));
    controls->addWidget(speedSlider);
    controls->addStretch();

    // 组合布局
    mainLayout->addWidget(lifeWidget, 1);
    mainLayout->addWidget(controlPanel);

    window.setCentralWidget(centralWidget);
    window.show();

    return app.exec();
}
