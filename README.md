# **Apartment rentals**
A simple apartment renting application built with C++/Qt and Django
## Build requirements
* python 3.7 and more 
* qt 5.15 and more
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
2. Open ApartmentRentals.sln with *Visual Studio*. 
3. In *Solution Explorer*, choose or open the solution.
4. Build the project
5. Run executable from target directory

## Run UnitTests

`docker-compose run app sh -c "python manage.py test"`

## Run e2e tests
1. Go to e2e folder
2. install requirements `pip install -r requirements.txt`
3. run `pytest /tests -vv`
