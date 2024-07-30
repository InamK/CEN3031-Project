# CEN3031-Project

## 1. How to run
1. You should copy the `mysql-connector-c-6.1.11-winx64\lib\libmysql.dll` and `mysql-connector-c-6.1.11-winx64\lib\libmysql.lib` in **cmake-build-debug** Folder.
2. You must have Directx 11 installed to run the GUI


## 2. DATABASE design

You can use docker to run mysql, or install mysql:5.7 in windows.
```
docker pull mysql:5.7
docker run --name mysql-container -e MYSQL_ROOT_PASSWORD=cen3031 -p 3306:3306 -d mysql:5.7 --skip_ssl
```

User table

| Field    | Type                            | Null | Key  | Default | Extra          |
|----------|---------------------------------|------|------|---------|----------------|
| id       | INT                             | NO   | PRI  | NULL    | AUTO_INCREMENT |
| username | VARCHAR(50)                     | NO   | UNI  | NULL    |                |
| password | VARCHAR(255)                    | NO   |      | NULL    |                |
| role     | ENUM('user', 'employee', 'admin') | NO   |      | NULL    |                |
| approved | BOOLEAN                         | YES  |      | FALSE   |                |



## Some commands





