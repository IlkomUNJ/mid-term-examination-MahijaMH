#include "drawingcanvas.h"
#include <fstream>
#include <vector>
#include <iostream>


DrawingCanvas::DrawingCanvas(QWidget *parent)
{
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints()
{
    m_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines()
{
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection()
{
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    const vector<int> windowSizes = {3, 5, 7};
    const double threshold = 0.6; // at least 60% pixels filled to consider it a line

    ofstream report("report.md", ios::trunc);
    if (!report.is_open()) {
        cerr << "Error: cannot open report.md for writing!" << endl;
        return;
    }

    report << "# Segment Detection Report\n\n";
    report << "Canvas size: " << image.width() << "x" << image.height() << "\n\n";

    for (int windowSize : windowSizes)
    {
        int radius = windowSize / 2;
        report << "## Window Size: " << windowSize << "x" << windowSize << "\n\n";

        long nonEmptyCount = 0;
        long matchCount = 0;

        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                vector<vector<bool>> window(windowSize, vector<bool>(windowSize, false));
                bool nonEmpty = false;

                for (int dx = -radius; dx <= radius; ++dx)
                {
                    for (int dy = -radius; dy <= radius; ++dy)
                    {
                        int px = x + dx;
                        int py = y + dy;
                        if (px < 0 || py < 0 || px >= image.width() || py >= image.height())
                            continue;

                        bool filled = (image.pixel(px, py) != 0xffffffff);
                        window[dx + radius][dy + radius] = filled;
                        if (filled)
                            nonEmpty = true;
                    }
                }

                if (!nonEmpty)
                    continue;

                nonEmptyCount++;
                report << "**Window at (" << x << "," << y << ")**\n";
                for (int i = 0; i < windowSize; ++i)
                {
                    for (int j = 0; j < windowSize; ++j)
                        report << (window[i][j] ? "1 " : "0 ");
                    report << "\n";
                }

                // Analyze horizontal / vertical / diagonal densities
                bool matched = false;
                string matchType = "";

                // horizontal check
                for (int i = 0; i < windowSize; ++i) {
                    int count = 0;
                    for (int j = 0; j < windowSize; ++j)
                        if (window[i][j]) count++;
                    if ((double)count / windowSize >= threshold) {
                        matched = true;
                        matchType = "Horizontal";
                        break;
                    }
                }

                // vertical check
                if (!matched) {
                    for (int j = 0; j < windowSize; ++j) {
                        int count = 0;
                        for (int i = 0; i < windowSize; ++i)
                            if (window[i][j]) count++;
                        if ((double)count / windowSize >= threshold) {
                            matched = true;
                            matchType = "Vertical";
                            break;
                        }
                    }
                }

                // diagonal checks
                if (!matched) {
                    int countMain = 0, countAnti = 0;
                    for (int i = 0; i < windowSize; ++i) {
                        if (window[i][i]) countMain++;
                        if (window[i][windowSize - 1 - i]) countAnti++;
                    }
                    if ((double)countMain / windowSize >= threshold) {
                        matched = true;
                        matchType = "Diagonal";
                    } else if ((double)countAnti / windowSize >= threshold) {
                        matched = true;
                        matchType = "AntiDiagonal";
                    }
                }

                if (matched) {
                    matchCount++;
                    report << "→ **Pattern Match:** " << matchType
                           << " at (" << x << "," << y << ")\n";
                }

                report << "\n";
            }
        }

        report << "**Total non-empty windows:** " << nonEmptyCount << "\n";
        report << "**Total matches:** " << matchCount << "\n\n";
    }

    report.close();
    cout << "All window dumps and fuzzy pattern matches saved to report.md" << endl;
}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint &point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if (isPaintLinesClicked) {
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for (int i = 0; i < m_points.size() - 1; i += 2) {
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i + 1]);
        }
        isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}
