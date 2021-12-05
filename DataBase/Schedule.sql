
DROP TABLE IF EXISTS users CASCADE;
DROP TABLE IF EXISTS groups_classes;
DROP TABLE IF EXISTS groups;
DROP TABLE IF EXISTS classes;
DROP TABLE IF EXISTS teachers;
DROP TABLE IF EXISTS universitys;



CREATE TABLE IF NOT EXISTS universitys(
	id 	  BIGSERIAL NOT NULL PRIMARY KEY,
	
	name  VARCHAR(40)
);


CREATE TABLE IF NOT EXISTS groups(
	id		       BIGSERIAL     NOT NULL PRIMARY KEY,
	
	university_id  BIGINT REFERENCES universitys(ID),
	faculty 	   VARCHAR(30),  
	course 		   smallint,
	group_name 	   varchar(10),
	num_subgroup   smallint
);

CREATE TABLE IF NOT EXISTS teachers(
	id	BIGSERIAL  NOT NULL PRIMARY KEY,
	
	first_name VARCHAR(20),
	last_name  VARCHAR(20),
	patronymic VARCHAR(20),
	chair      VARCHAR(40),
	position   VARCHAR(30)
);

CREATE TABLE IF NOT EXISTS classes(
	id		 	 BIGSERIAL 		
		NOT NULL PRIMARY KEY,

	dayofweek 	 SMALLINT,
	numberclass  SMALLINT,
	week 		 BOOL,
	subgroup 	 SMALLINT,
	curricula 	 VARCHAR(50),
	teacher_id   BIGINT REFERENCES teachers(ID),
	audience     VARCHAR(8),
	date 		 DATE,
	expiration   date
);

CREATE TABLE IF NOT EXISTS groups_classes(
	id 		  BIGSERIAL   
		NOT NULL PRIMARY KEY,
	
	group_id  BIGINT  NOT NULL REFERENCES groups(id),
	class_id  BIGINT  NOT NULL REFERENCES classes(id)
);

CREATE TABLE IF NOT EXISTS users(
	id        BIGSERIAL 	
		NOT NULL PRIMARY KEY,
	
	username  varchar(30)   NOT NULL UNIQUE,
	password  varchar(255)  NOT NULL
);

CREATE TABLE IF NOT EXISTS students(
	group_ID  BIGINT  REFERENCES groups(id),
	subgroup  smallint
) INHERITS(users);

CREATE TABLE IF NOT EXISTS teachers_accoutns(
	teacher_ID  BIGINT  REFERENCES teachers(id)
) INHERITS(users);

CREATE TABLE IF NOT EXISTS admins(
) INHERITS(users);


INSERT INTO universitys (name)  VALUES('БрГТУ');
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'ФЭИС', 3, 'МС-5', 2);
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'ФЭИС', 3, 'ПЭ-20', 2); 
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'ФЭИС', 3, 'Э-58', 2); 
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'ФЭИС', 3, 'ПО-4', 2); 
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'ФЭИС', 3, 'ПО-5', 2); 
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'ФЭИС', 3, 'ИИ-17', 2);
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'ФЭИС', 4, 'МС-4', 2);
INSERT INTO groups (university_id, faculty, course, group_name, num_subgroup) VALUES (1, 'МСФ', 2, 'С-1', 2);

INSERT INTO teachers (first_name, last_name, patronymic, chair, position) VALUES ('Сергей', 'Лапич', 'Вячеславович', 'ЭВМСиС', 'Старший преподаватель'); 
INSERT INTO teachers (first_name, last_name, patronymic, chair, position) VALUES ('Станислав', 'Дереченик' , 'Станиславович', 'ЭВМСиС', 'Старший преподаватель'); 
INSERT INTO teachers (first_name, last_name, patronymic, chair, position) VALUES ('Станислав', 'Дереченик' , 'Станиславович', 'ЭВМСиС', 'Заведующий кафедрой'); 

INSERT INTO classes (dayofweek, numberclass, week, curricula, teacher_id, audience) VALUES (2, 1, TRUE, 'ОиОКСИС', 1, '2/103');
INSERT INTO classes (dayofweek, numberclass, week, curricula, teacher_id, audience) VALUES (2, 2, TRUE, 'ВМС', 1, '2/401a');
INSERT INTO classes (dayofweek, numberclass, week, curricula, teacher_id, audience) VALUES (2, 3, TRUE, 'ММТИиУ', 2, '2/410a');

INSERT INTO groups_classes (group_id, class_id) VALUES(1, 1);
INSERT INTO groups_classes (group_id, class_id) VALUES(1, 2);
INSERT INTO groups_classes (group_id, class_id) VALUES(1, 3);

INSERT INTO students (username, password, group_id, subgroup) VALUES ('user', 'user', 1, 1);
INSERT INTO admins (username, password) VALUES ('admin', 'admin');


SELECT classes.curricula, teachers.last_name, groups.group_name
FROM classes 
JOIN teachers ON classes.teacher_id = teachers.id
JOIN groups_classes ON classes.id = groups_classes.class_id
JOIN groups ON groups.id = groups_classes.group_id;

SELECT DISTINCT groups.faculty FROM groups
JOIN universitys ON universitys.name = 'БрГТУ'
ORDER BY groups.faculty;

SELECT * FROM groups
JOIN universitys ON universitys.name = 'БрГТУ'
WHERE groups.faculty = 'ФЭИС' AND groups.course = '3' AND groups.group_name = 'МС-5'
ORDER BY groups.course;




SELECT * FROM users WHERE username = 'user' AND password = 'user';
SELECT * FROM universitys;
SELECT * FROM teachers;
SELECT * FROM groups;
