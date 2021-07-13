#pragma once

#include <set>
#include <QTableWidget>

class QPushButton;
class QToolButton;
class QComboBox;
class QSpinBox;
class QDate;

#include "Models.h"

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget* parent=nullptr);
    ~TableWidget();

    virtual void onDeleteItem(int row, int id) = 0;
    virtual void onSaveItem(int row, int id) = 0;
    virtual void onCancelItem(int row, int id) = 0;

public slots:
    void setColumnsCount(int columnsCount);
    void setHeaders(const QStringList& headers);

    void removeRow(int row);

    void onCellEdited(int row, int col);

    void onCellClicked(int row, int col);
    void onCurrentCellChanged(int row, int col, int prevRow, int prevCol);

    void addItem(int row, int col, bool isEditable, const QString& value);
    void addTimeItem(int row, int col, bool isEditable, int value);
    void addDateItem(int row, int col, bool isEditable, const QDate& date);
    void addComboBox(int row, int col, const QString& state, const QStringList& states);
    void addSpinBox(int row, int col, int minValue, int maxValue, int value, bool disabled);
    void addButtons(int row, int col);

    void saveAll();
    void discardAll();

    bool isRowChanged();
protected:
    int getButtonRowIndex(QToolButton* clickedButton, const QString& groupName);
   
    void initializeColRowValues(int size);
    void configureSave(int row);
    bool isRowChanged(int row);

    void createMembers();
    void initializeMembers();
    void setupLayouts();
    void makeConnections();

signals:
    void clickedOnDelete(int id);
    void clickedOnDeleteAll(std::vector<int> id);
    void clickedOnSave(int id, const QJsonObject& object);

protected:
    int m_rowsCount;
    int m_colsCount;
    std::vector<std::vector<QString>> m_cellValues;
    std::vector<bool> m_changedRows;
    std::map<int, QComboBox*> m_rowToComboBoxMapping;
    std::map<int, QString> m_columnWidgetType;
private:
    int m_lastSelectedRow;
    int m_lastSelectedCol;
    std::map<QString, std::vector<QToolButton*>> m_stringToButtonsMapping;
    QStringList m_columnHeaders;
};
