# **Apartment rentals**
A simple apartment renting application built with C++/Qt and Django
## Build requirements
* Python 3.7 and more 
* Qt 5.15 or above
## Local Building

Clone the repository.

To be able to use the application, you'll need to 
* start the server
* build and start the client application

### Start Server
Go to server folder and run
 
 `docker-compose up --build`

By deafult server will be started at http://localhost:8000/

### Build and Start Client
1. Go to client folder 
2. Open [ApartmentRentals.sln](client/ApartmentRentals.sln) with *Visual Studio*. 
3. Build&Run the project

## Run UnitTests

`docker-compose run app sh -c "python manage.py test"`

## Run e2e tests
1. Go to e2e folder
2. install requirements `pip install -r requirements.txt`
3. run `pytest /tests -vv`
