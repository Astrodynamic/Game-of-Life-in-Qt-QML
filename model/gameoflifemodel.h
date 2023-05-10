#ifndef GAMEOFLIFEMODEL_H
#define GAMEOFLIFEMODEL_H

#include <array>
#include <QAbstractTableModel>
#include <QPoint>

class GameOfLifeModel : public QAbstractTableModel {
    Q_OBJECT
    Q_ENUMS(Roles)

    Q_PROPERTY(int height READ getHeight CONSTANT)
    Q_PROPERTY(int width READ getWidth CONSTANT)

public:
    enum Roles {
        CellRole
    };

    QHash<int, QByteArray> roleNames() const override {
        return {
            { CellRole, "value" }
        };
    }

    explicit GameOfLifeModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE void nextStep();
    Q_INVOKABLE bool loadFile(const QString &fileName);
    Q_INVOKABLE void loadPattern(const QString &plainText);
    Q_INVOKABLE void clear();

    static int getWidth();
    static int getHeight();

private:
    static constexpr int width = 50;
    static constexpr int height = 50;
    static constexpr int size = width * height;

    using StateContainer = std::array<bool, size>;
    StateContainer m_currentState;

    int cellNeighborsCount(const QPoint &cellCoordinates) const;
    static bool areCellCoordinatesValid(const QPoint &coordinates);
    static QPoint cellCoordinatesFromIndex(int cellIndex);
    static std::size_t cellIndex(const QPoint &coordinates);
};

#endif // GAMEOFLIFEMODEL_H
