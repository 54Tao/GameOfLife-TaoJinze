#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>

class LifeWidget : public QWidget {
    Q_OBJECT
public:
    explicit LifeWidget(QWidget *parent = nullptr);
    void start(int interval = 100);
    void stop();
    void clear();
    void randomize();

public slots:
    void toggleSimulation();
    void setInterval(int milliseconds);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    int m_cellSize = 20;
    bool m_running = false;
    QTimer m_timer;
    QVector<QVector<bool>> m_grid;
    QVector<QVector<bool>> m_nextGrid;

    int countNeighbors(int x, int y) const;
    void updateGrid();
    void drawGrid(QPainter &painter);
    void drawCells(QPainter &painter);
    QPoint cellAt(const QPoint &pos) const;
};

#endif // LIFEWIDGET_H
