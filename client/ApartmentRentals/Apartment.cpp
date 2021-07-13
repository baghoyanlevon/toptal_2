#include "Apartment.h"
#include "Realtor.h"

#include "User.h"

int Apartment::getId() const { return id; }
void Apartment::setId(int val) { id = val; }
int Apartment::getUserId() const
{
    return user_id;
}
void Apartment::setUserId(int val)
{
    user_id = val;
}
QString Apartment::getName() const { return m_name; }
void Apartment::setName(QString val) { m_name = val; }
QString Apartment::getDescription() const { return m_description; }
void Apartment::setDescription(QString val) { m_description = val; }
float Apartment::getFloorSize() const { return m_floorSize; }
void Apartment::setFloorSize(float val) { m_floorSize = val; }
int Apartment::getPrice() const { return m_price; }
void Apartment::setPrice(int val) { m_price = val; }
int Apartment::getRoomsNum() const { return m_roomsNum; }
void Apartment::setRoomsNum(int val) { m_roomsNum = val; }
double Apartment::getLocLatitude() const { return m_locLatitude; }
void Apartment::setLocLatitude(double val) { m_locLatitude = val; }
double Apartment::getLocLongitude() const { return m_locLongitude; }
void Apartment::setLocLongitude(double val) { m_locLongitude = val; }
QDate Apartment::getDateAdded() const { return m_dateAdded; }
void Apartment::setDateAdded(const QDate& val) { m_dateAdded = val; }
std::pair<QString, int> Apartment::getRealtor() const { return m_realtor; }
void Apartment::setRealtor(const QString& realtorEmail, int id) { m_realtor = std::make_pair(realtorEmail, id); }
bool Apartment::getRented() const { return m_isRented; }
void Apartment::setRented(bool val) { m_isRented = val; }

QJsonObject Apartment::toJson()
{
	QJsonObject object; 
	
    object["name"] = m_name;
    object["id"] = id;
    object["rented"] = m_isRented;
    object["date"] = m_dateAdded.toString("yyyy-MM-dd");
    object["description"] = m_description;
    object["floor_area_size"] = m_floorSize;
    object["price_per_month"] = m_price;
    object["number_of_rooms"] = m_roomsNum;
    object["latitude"] = m_locLatitude;
    object["longitude"] = m_locLongitude;
    if (ActiveUser->isAdmin()) {
        object["user"] = user_id;
    }
	return object;
}

void Apartment::initializeFromJson(const QJsonObject& object)
{
    id = object["id"].toInt();
    m_name = object["name"].toString();
    m_isRented = object["rented"].toBool();
    m_dateAdded = QDate::fromString(object["date"].toString(), "yyyy-MM-dd");
    m_description = object["description"].toString();
    m_floorSize = object["floor_area_size"].toDouble();
    m_price = object["price_per_month"].toInt();
    m_roomsNum = object["number_of_rooms"].toInt();
    m_locLatitude = object["latitude"].toString().toDouble();
    m_locLongitude = object["longitude"].toString().toDouble();
    if (ActiveUser->isAdmin()) {
        user_id = object["user"].toInt();
    }
}

void ApartmentsModel::initializeFromJson(const QJsonArray& jsonArray)
{
    models.clear();
    for (auto const& item : jsonArray) {
        Apartment currentRecord;
        currentRecord.initializeFromJson(item.toObject());
        models.push_back(currentRecord);
    }
}
