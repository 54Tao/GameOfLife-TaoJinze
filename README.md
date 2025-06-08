# Conway's Game of Life

这是一个使用 Qt 框架实现的康威生命游戏(Conway's Game of Life)。

## 功能特点

- 交互式网格界面
- 开始/停止模拟
- 清空网格
- 随机生成细胞
- 速度控制
- 鼠标绘制细胞

## 构建要求

- Qt 5.x 或更高版本
- CMake 3.x 或更高版本
- C++ 编译器(支持 C++11 或更高版本)

## 构建步骤

1. 克隆仓库:
```bash
git clone https://github.com/54Tao/GameOfLife-TaoJinze.git
cd GameOfLife-TaoJinze
```

2. 创建构建目录:
```bash
mkdir build
cd build
```

3. 配置和构建:
```bash
cmake ..
make
```

4. 运行程序:
```bash
./GameOfLife
```

## 使用说明

- 点击"开始"按钮开始模拟
- 使用"清空"按钮清除所有细胞
- 使用"随机"按钮随机生成细胞
- 使用速度滑块调整模拟速度
- 使用鼠标点击或拖动来绘制/擦除细胞

## 许可证

MIT License 
