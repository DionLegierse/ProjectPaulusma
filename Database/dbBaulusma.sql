PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
COMMIT;


CREATE TABLE tblYear(
intYear int
);


CREATE TABLE tblDate(
ID integer, 
intYear integer references tblYear(intYear), 
txtDate string
);

CREATE TABLE tblTime(
ID integer, 
txtHour string, 
txtMinute string
);

CREATE TABLE tblDateTime(
ID integer, 
txtDate string references tblDate(txtDate), 
txtHour string references tblTime(txtHour)
);

CREATE TABLE tblValues(
ID integer, 
intPressure integer, 
intHumidity integer, 
intTempature integer
);

CREATE TABLE tblTimeValues(
ID integer, 
TimeID integer references tblDateTime(ID), 
ValueID integer references tblValues(ID)
);