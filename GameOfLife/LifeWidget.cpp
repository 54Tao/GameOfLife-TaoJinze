#include "LifeWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRandomGenerator>

constexpr int GRID_WIDTH = 40;
constexpr int GRID_HEIGHT = 25;

LifeWidget::LifeWidget(QWidget *parent)
    : QWidget(parent),
    m_grid(GRID_WIDTH, QVector<bool>(GRID_HEIGHT, false)),
    m_nextGrid(GRID_WIDTH, QVector<bool>(GRID_HEIGHT, false))
{
    setFixedSize(GRID_WIDTH * m_cellSize, GRID_HEIGHT * m_cellSize);
    connect(&m_timer, &QTimer::timeout, this, &LifeWidget::updateGrid);
}

void LifeWidget::start(int interval) {
    m_timer.start(interval);
    m_running = true;
}

void LifeWidget::stop() {
    m_timer.stop();
    m_running = false;
}

void LifeWidget::clear() {
    m_grid.fill(QVector<bool>(GRID_HEIGHT, false));
    update();
}

void LifeWidget::randomize() {
    for (auto &col : m_grid) {
        for (auto &cell : col) {
            cell = QRandomGenerator::global()->bounded(4) == 0;
        }
    }
    update();
}

int LifeWidget::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = (x + dx + GRID_WIDTH) % GRID_WIDTH;
            int ny = (y + dy + GRID_HEIGHT) % GRID_HEIGHT;
            count += m_grid[nx][ny] ? 1 : 0;
        }
    }
    return count;
}

void LifeWidget::updateGrid() {
    m_nextGrid = m_grid;

    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int neighbors = countNeighbors(x, y);
            m_nextGrid[x][y] = (neighbors == 3) || (m_grid[x][y] && neighbors == 2);
        }
    }

    std::swap(m_grid, m_nextGrid);
    update();
}

void LifeWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    painter.fillRect(rect(), QColor(35, 35, 40));

    // 绘制细胞
    drawCells(painter);

    // 绘制网格线
    drawGrid(painter);
}

void LifeWidget::drawGrid(QPainter &painter) {
    painter.setPen(QColor(60, 60, 70));

    // 绘制垂直线
    for (int x = 0; x <= GRID_WIDTH; ++x) {
        painter.drawLine(x * m_cellSize, 0,
                         x * m_cellSize, height());
    }

    // 绘制水平线
    for (int y = 0; y <= GRID_HEIGHT; ++y) {
        painter.drawLine(0, y * m_cellSize,
                         width(), y * m_cellSize);
    }
}

void LifeWidget::drawCells(QPainter &painter) {
    painter.setBrush(QColor(85, 170, 255));
    painter.setPen(Qt::NoPen);

    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            if (m_grid[x][y]) {
                painter.drawRoundedRect(
                    x * m_cellSize + 1,
                    y * m_cellSize + 1,
                    m_cellSize - 2,
                    m_cellSize - 2,
                    3, 3
                    );
            }
        }
    }
}

QPoint LifeWidget::cellAt(const QPoint &pos) const {
    return QPoint(
        pos.x() / m_cellSize,
        pos.y() / m_cellSize
        );
}

void LifeWidget::mousePressEvent(QMouseEvent *event) {
    QPoint cell = cellAt(event->pos());
    if (cell.x() >= 0 && cell.x() < GRID_WIDTH &&
        cell.y() >= 0 && cell.y() < GRID_HEIGHT) {
        m_grid[cell.x()][cell.y()] = !m_grid[cell.x()][cell.y()];
        update();
    }
}

void LifeWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint cell = cellAt(event->pos());
        if (cell.x() >= 0 && cell.x() < GRID_WIDTH &&
            cell.y() >= 0 && cell.y() < GRID_HEIGHT) {
            m_grid[cell.x()][cell.y()] = true;
            update();
        }
    }
}

void LifeWidget::setInterval(int milliseconds) {
    m_timer.setInterval(milliseconds);
}

void LifeWidget::toggleSimulation() {
    m_running ? stop() : start();
}
