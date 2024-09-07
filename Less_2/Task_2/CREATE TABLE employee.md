CREATE TABLE employee (
id_employee INTEGER PRIMARY KEY,
name_employee VARCHAR(50),
id_department INTEGER,
id_boss INTEGER REFERENCES employee (id_employee)

)