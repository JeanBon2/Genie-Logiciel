DROP TABLE IF EXISTS HealthPrintAttributeValues;
DROP TABLE IF EXISTS PotentialDiseasesAndLinkedAttributes;
DROP TABLE IF EXISTS DiscreteNormalValues;
DROP TABLE IF EXISTS ContinuousNormalValues;
DROP TABLE IF EXISTS DiscriminantAttributes;
DROP TABLE IF EXISTS Attributes;
DROP TABLE IF EXISTS PotentialDiseases;
DROP TABLE IF EXISTS Diseases;
DROP TABLE IF EXISTS Analyses;
DROP TABLE IF EXISTS HealthPrints;

/* Tables shared with server */
CREATE TABLE Diseases (
	diseaseId integer primary key autoincrement,
	diseaseName text NOT NULL
);

CREATE TABLE Attributes (
	attributeId integer primary key autoincrement,
	name text NOT NULL,
	discrete integer NOT NULL
);

CREATE TABLE DiscriminantAttributes (
	discriminantAttributeId integer primary key autoincrement,
	diseaseId integer NOT NULL,
	attributeId integer NOT NULL,
	FOREIGN KEY(diseaseId) REFERENCES Diseases(diseaseId),
	FOREIGN KEY(attributeId) REFERENCES Attributes(attributeId)
);

CREATE TABLE ContinuousNormalValues (
	continuousNormalValues integer primary key autoincrement,
	attributeId integer NOT NULL,
	minimumValue real,
	maximumValue real,
	FOREIGN KEY(attributeId) REFERENCES Attributes(attributeId)
);

CREATE TABLE DiscreteNormalValues (
	discreteNormalValues integer primary key autoincrement,
	attributeId integer NOT NULL,
	normalValue real NOT NULL,
	normalValueName text,
	FOREIGN KEY(attributeId) REFERENCES Attributes(attributeId)
);

/* Local tables */
CREATE TABLE HealthPrints (
	healthPrintId integer primary key autoincrement,
	patientName text NOT NULL,
	doctorName text,
	printDate text,
	sensorId integer
);

CREATE TABLE HealthPrintAttributeValues (
	healthPrintAttributeValuesId integer primary key autoincrement,
	healthPrintId integer NOT NULL,
	attributeId integer NOT NULL,
	attributeValue real,
	valueName text,
	FOREIGN KEY(healthPrintId) REFERENCES HealthPrints(healthPrintId),
	FOREIGN KEY(attributeId) REFERENCES Attributes(attributeId)
);

CREATE TABLE Analyses (
	analyseId integer primary key autoincrement,
	healthPrintId integer NOT NULL,
	FOREIGN KEY(healthPrintId) REFERENCES HealthPrints(healthPrintId)
);

CREATE TABLE PotentialDiseases (
	potentialDiseaseId integer primary key autoincrement,
	analyseId integer NOT NULL,
	diseaseId integer NOT NULL,
	matchingRate real NOT NULL,
	FOREIGN KEY(analyseId) REFERENCES Analyses(analyseId),
	FOREIGN KEY(diseaseId) REFERENCES Diseases(diseaseId)
);

CREATE TABLE AbnormalAttributes (
	potentialDiseasesAndLinkedAttributesId integer primary key NOT NULL,
	analyseId integer NOT NULL,
	potentialDiseaseId integer NOT NULL,
	healthPrintAttributeValuesId integer NOT NULL,
	FOREIGN KEY(analyseId) REFERENCES Analyses(analyseId),
	FOREIGN KEY(potentialDiseaseId) REFERENCES PotentialDiseases(potentialDiseaseId)
);