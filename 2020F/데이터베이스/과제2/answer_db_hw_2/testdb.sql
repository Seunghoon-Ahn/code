-- MySQL dump 10.13  Distrib 8.0.18, for Win64 (x86_64)
--
-- Host: localhost    Database: testdb
-- ------------------------------------------------------
-- Server version	8.0.18

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `advisor`
--

DROP TABLE IF EXISTS `advisor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `advisor` (
  `student_id` varchar(45) NOT NULL COMMENT '학생 아이디',
  `professor_id` varchar(45) NOT NULL COMMENT '교수 아이디',
  PRIMARY KEY (`student_id`),
  KEY `FK_Advisor_professor_id_Professor_professor_id` (`professor_id`),
  CONSTRAINT `FK_Advisor_professor_id_Professor_professor_id` FOREIGN KEY (`professor_id`) REFERENCES `professor` (`professor_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_Advisor_student_id_Student_student_id` FOREIGN KEY (`student_id`) REFERENCES `student` (`student_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `advisor`
--

LOCK TABLES `advisor` WRITE;
/*!40000 ALTER TABLE `advisor` DISABLE KEYS */;
INSERT INTO `advisor` VALUES ('20150005','1'),('20160006','1'),('20200023','1'),('20180012','10'),('20160019','11'),('20160021','13'),('20170017','14'),('20180001','2'),('20170002','3'),('20180004','4'),('20160009','6'),('20160010','8');
/*!40000 ALTER TABLE `advisor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `computer_science_student`
--

DROP TABLE IF EXISTS `computer_science_student`;
/*!50001 DROP VIEW IF EXISTS `computer_science_student`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `computer_science_student` AS SELECT 
 1 AS `student_id`,
 1 AS `student_name`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `course`
--

DROP TABLE IF EXISTS `course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `course` (
  `course_id` varchar(45) NOT NULL COMMENT '강의 아이디',
  `title` varchar(45) NOT NULL COMMENT '강의명',
  `dept_name` varchar(45) NOT NULL COMMENT '학과명',
  `credit` int(11) DEFAULT NULL,
  PRIMARY KEY (`course_id`),
  KEY `FK_Course_dept_name_Department_dept_name` (`dept_name`),
  CONSTRAINT `FK_Course_dept_name_Department_dept_name` FOREIGN KEY (`dept_name`) REFERENCES `department` (`dept_name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course`
--

LOCK TABLES `course` WRITE;
/*!40000 ALTER TABLE `course` DISABLE KEYS */;
INSERT INTO `course` VALUES ('1','자료구조','컴퓨터학부',3),('11','자료구조','미디어학부',3),('12','운영체제','미디어학부',3),('13','데이터베이스','미디어학부',3),('14','알고리즘','미디어학부',3),('15','프로그래밍','미디어학부',3),('16','리눅스시스템프로그래밍','미디어학부',3),('2','운영체제','컴퓨터학부',3),('21','자료구조','소프트웨어학부',3),('22','운영체제','소프트웨어학부',3),('23','데이터베이스','소프트웨어학부',3),('24','알고리즘','소프트웨어학부',3),('25','프로그래밍','소프트웨어학부',3),('26','리눅스시스템프로그래밍','소프트웨어학부',3),('3','데이터베이스','컴퓨터학부',3),('4','파일처리','컴퓨터학부',2),('5','알고리즘','컴퓨터학부',3),('6','정보보안','컴퓨터학부',1),('7','프로그래밍','컴퓨터학부',3),('8','리눅스시스템프로그래밍','컴퓨터학부',3);
/*!40000 ALTER TABLE `course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `department`
--

DROP TABLE IF EXISTS `department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `department` (
  `dept_name` varchar(45) NOT NULL COMMENT '학과명',
  `budget` int(11) NOT NULL COMMENT '예산',
  PRIMARY KEY (`dept_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `department`
--

LOCK TABLES `department` WRITE;
/*!40000 ALTER TABLE `department` DISABLE KEYS */;
INSERT INTO `department` VALUES ('미디어학부',150),('소프트웨어학부',200),('컴퓨터학부',300);
/*!40000 ALTER TABLE `department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `dept_average_credit`
--

DROP TABLE IF EXISTS `dept_average_credit`;
/*!50001 DROP VIEW IF EXISTS `dept_average_credit`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `dept_average_credit` AS SELECT 
 1 AS `dept_name`,
 1 AS `avg_credit`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary view structure for view `no_exist_advisor_student`
--

DROP TABLE IF EXISTS `no_exist_advisor_student`;
/*!50001 DROP VIEW IF EXISTS `no_exist_advisor_student`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `no_exist_advisor_student` AS SELECT 
 1 AS `student_id`,
 1 AS `student_name`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary view structure for view `operating_system_professor`
--

DROP TABLE IF EXISTS `operating_system_professor`;
/*!50001 DROP VIEW IF EXISTS `operating_system_professor`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `operating_system_professor` AS SELECT 
 1 AS `dept_name`,
 1 AS `professor_name`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `prereq`
--

DROP TABLE IF EXISTS `prereq`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `prereq` (
  `course_id` varchar(45) NOT NULL COMMENT '강의 아이디',
  `prereq_id` varchar(45) NOT NULL COMMENT '선수강의 아이디',
  PRIMARY KEY (`course_id`,`prereq_id`),
  KEY `FK_Prereq_prereq_id_Course_course_id` (`prereq_id`),
  CONSTRAINT `FK_Prereq_course_id_Course_course_id` FOREIGN KEY (`course_id`) REFERENCES `course` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_Prereq_prereq_id_Course_course_id` FOREIGN KEY (`prereq_id`) REFERENCES `course` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prereq`
--

LOCK TABLES `prereq` WRITE;
/*!40000 ALTER TABLE `prereq` DISABLE KEYS */;
INSERT INTO `prereq` VALUES ('5','1'),('14','11'),('11','15'),('24','21'),('21','25'),('1','7');
/*!40000 ALTER TABLE `prereq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `professor`
--

DROP TABLE IF EXISTS `professor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `professor` (
  `professor_id` varchar(45) NOT NULL COMMENT '교수 아이디',
  `professor_name` varchar(45) NOT NULL COMMENT '교수 이름',
  `dept_name` varchar(45) NOT NULL COMMENT '학과명',
  `salary` int(11) NOT NULL COMMENT '연봉',
  `start_date` date NOT NULL COMMENT '임용날짜',
  PRIMARY KEY (`professor_id`),
  KEY `FK_Professor_dept_name_Department_dept_name` (`dept_name`),
  CONSTRAINT `FK_Professor_dept_name_Department_dept_name` FOREIGN KEY (`dept_name`) REFERENCES `department` (`dept_name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `professor`
--

LOCK TABLES `professor` WRITE;
/*!40000 ALTER TABLE `professor` DISABLE KEYS */;
INSERT INTO `professor` VALUES ('1','김윤석','컴퓨터학부',100,'2010-03-01'),('10','고성훈','미디어학부',50,'2018-03-01'),('11','안혜진','소프트웨어학부',100,'2001-03-01'),('12','조혜은','소프트웨어학부',60,'2017-03-01'),('13','김유나','소프트웨어학부',80,'2013-03-01'),('14','김용묵','소프트웨어학부',70,'2014-03-01'),('15','지어진','소프트웨어학부',50,'2019-03-01'),('2','염동혁','컴퓨터학부',50,'2018-03-01'),('3','최지혁','컴퓨터학부',70,'2015-03-01'),('4','박승수','컴퓨터학부',60,'2014-03-01'),('5','이정석','컴퓨터학부',80,'2012-03-01'),('6','최도용','미디어학부',70,'2014-03-01'),('7','지영환','미디어학부',60,'2016-03-01'),('8','장성환','미디어학부',50,'2019-03-01'),('9','정지훈','미디어학부',100,'2012-03-01');
/*!40000 ALTER TABLE `professor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `section`
--

DROP TABLE IF EXISTS `section`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `section` (
  `course_id` varchar(45) NOT NULL COMMENT '강의 아이디',
  `section_id` char(1) NOT NULL DEFAULT '가' COMMENT '분반 아이디',
  `semester` varchar(45) NOT NULL COMMENT '학기',
  `year` varchar(10) NOT NULL COMMENT '년도',
  PRIMARY KEY (`course_id`,`section_id`,`semester`,`year`),
  CONSTRAINT `FK_Section_course_id_Course_course_id` FOREIGN KEY (`course_id`) REFERENCES `course` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `section`
--

LOCK TABLES `section` WRITE;
/*!40000 ALTER TABLE `section` DISABLE KEYS */;
INSERT INTO `section` VALUES ('1','가','Spring','2017'),('1','가','Spring','2018'),('1','가','Spring','2019'),('1','가','Spring','2020'),('11','가','Fall','2017'),('11','가','Spring','2019'),('11','가','Spring','2020'),('12','가','Fall','2019'),('12','나','Fall','2019'),('13','가','Spring','2019'),('13','나','Spring','2019'),('14','가','Fall','2018'),('15','가','Spring','2017'),('16','가','Spring','2018'),('2','가','Fall','2017'),('2','가','Fall','2018'),('2','나','Fall','2017'),('2','나','Fall','2018'),('21','가','Spring','2017'),('21','가','Spring','2019'),('21','가','Spring','2020'),('22','가','Fall','2019'),('22','나','Fall','2019'),('23','가','Spring','2019'),('23','나','Spring','2019'),('24','가','Fall','2018'),('25','가','Fall','2017'),('26','가','Spring','2018'),('3','가','Spring','2018'),('3','가','Spring','2019'),('3','나','Spring','2018'),('3','나','Spring','2019'),('4','가','Fall','2017'),('4','가','Fall','2018'),('4','가','Fall','2019'),('5','가','Fall','2017'),('5','가','Fall','2018'),('6','가','Fall','2017'),('6','가','Fall','2018'),('6','가','Fall','2019'),('7','가','Fall','2017'),('7','가','Fall','2019'),('7','가','Spring','2018'),('8','가','Spring','2018');
/*!40000 ALTER TABLE `section` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student` (
  `student_id` varchar(45) NOT NULL COMMENT '학생 아이디',
  `student_name` varchar(45) NOT NULL COMMENT '학생 이름',
  `dept_name` varchar(45) NOT NULL COMMENT '학과명',
  `admission_date` date DEFAULT NULL,
  `home_address` varchar(45) NOT NULL COMMENT '집주소',
  PRIMARY KEY (`student_id`),
  KEY `FK_Student_dept_name_Department_dept_name` (`dept_name`),
  CONSTRAINT `FK_Student_dept_name_Department_dept_name` FOREIGN KEY (`dept_name`) REFERENCES `department` (`dept_name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('20150005','구본휘','컴퓨터학부','2015-03-01','서울'),('20150013','이덕정','미디어학부','2015-03-01','대구'),('20150020','최영림','소프트웨어학부','2015-03-01','대전'),('20160006','유민욱','컴퓨터학부','2016-03-01','인천'),('20160009','박동희','미디어학부','2016-03-01','서울'),('20160010','김재환','미디어학부','2016-03-01','부산'),('20160016','강유리','미디어학부','2016-03-01','부산'),('20160019','윤성준','소프트웨어학부','2016-03-01','서울'),('20160021','황인건','소프트웨어학부','2016-03-01','대구'),('20160024','송누리','소프트웨어학부','2016-03-01','부산'),('20170002','김경남','컴퓨터학부','2017-03-01','부산'),('20170011','성영식','미디어학부','2017-03-01','인천'),('20170017','강현지','소프트웨어학부','2017-03-01','서울'),('20170018','신연수','소프트웨어학부','2017-03-01','서울'),('20180001','구기성','컴퓨터학부','2018-03-01','서울'),('20180003','김아정','컴퓨터학부','2018-03-01','대구'),('20180004','김재섭','컴퓨터학부','2018-03-01','서울'),('20180012','김효정','미디어학부','2018-03-01','대전'),('20190007','이규현','컴퓨터학부','2019-03-01','서울'),('20190015','이승혁','미디어학부','2019-03-01','서울'),('20190022','김준섭','소프트웨어학부','2019-03-01','부산'),('20200008','권현석','컴퓨터학부','2020-03-01','서울'),('20200014','이동곤','미디어학부','2020-03-01','서울'),('20200023','김승석','소프트웨어학부','2020-03-01','서울');
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `takes`
--

DROP TABLE IF EXISTS `takes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `takes` (
  `student_id` varchar(45) NOT NULL COMMENT '학생 아이디',
  `course_id` varchar(45) NOT NULL COMMENT '강의 아이디',
  `section_id` char(1) NOT NULL COMMENT '분반 아이디',
  `semester` varchar(45) NOT NULL COMMENT '학기',
  `year` varchar(10) NOT NULL COMMENT '년도',
  `grade` char(1) DEFAULT 'F' COMMENT '등급',
  PRIMARY KEY (`student_id`,`course_id`,`section_id`,`semester`,`year`),
  KEY `FK_Takes_course_id_Section_course_id` (`course_id`,`section_id`,`semester`,`year`),
  CONSTRAINT `FK_Takes_course_id_Section_course_id` FOREIGN KEY (`course_id`, `section_id`, `semester`, `year`) REFERENCES `section` (`course_id`, `section_id`, `semester`, `year`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_Takes_student_id_Student_student_id` FOREIGN KEY (`student_id`) REFERENCES `student` (`student_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `takes`
--

LOCK TABLES `takes` WRITE;
/*!40000 ALTER TABLE `takes` DISABLE KEYS */;
INSERT INTO `takes` VALUES ('20150005','2','나','Fall','2017','B'),('20150005','3','나','Spring','2019','A'),('20150013','14','가','Fall','2018','B'),('20150020','21','가','Spring','2017','B'),('20160006','2','가','Fall','2017','A'),('20160006','4','가','Fall','2017','A'),('20160006','7','가','Fall','2017','A'),('20160009','13','가','Spring','2019','A'),('20160010','13','나','Spring','2019','B'),('20160016','16','가','Spring','2018','B'),('20160019','22','나','Fall','2019','A'),('20160021','25','가','Fall','2017','B'),('20160024','26','가','Spring','2018','A'),('20170002','1','가','Spring','2017','B'),('20170002','2','나','Fall','2018','B'),('20170002','3','가','Spring','2019','C'),('20170002','4','가','Fall','2019','A'),('20170002','5','가','Fall','2017','D'),('20170002','6','가','Fall','2019','B'),('20170002','7','가','Fall','2019','A'),('20170002','8','가','Spring','2018','A'),('20170011','11','가','Fall','2017','A'),('20170011','12','나','Fall','2019','B'),('20170011','13','나','Spring','2019','A'),('20170011','14','가','Fall','2018','B'),('20170011','15','가','Spring','2017','B'),('20170011','16','가','Spring','2018','A'),('20170017','21','가','Spring','2017','C'),('20170017','22','가','Fall','2019','A'),('20170017','23','가','Spring','2019','A'),('20170017','24','가','Fall','2018','B'),('20170017','25','가','Fall','2017','B'),('20170017','26','가','Spring','2018','D'),('20170018','24','가','Fall','2018','A'),('20180001','2','나','Fall','2018','A'),('20180001','3','나','Spring','2019','B'),('20180001','4','가','Fall','2018','B'),('20180003','1','가','Spring','2018','A'),('20180003','3','가','Spring','2018','A'),('20180003','7','가','Spring','2018','A'),('20180003','8','가','Spring','2018','A'),('20180004','1','가','Spring','2019','F'),('20180004','4','가','Fall','2018','B'),('20180012','12','가','Fall','2019','A'),('20190007','3','나','Spring','2019','B'),('20190015','11','가','Spring','2019','A'),('20190022','23','가','Spring','2019','F'),('20200008','1','가','Spring','2020','B'),('20200014','11','가','Spring','2020','B'),('20200023','21','가','Spring','2020','A');
/*!40000 ALTER TABLE `takes` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `update_total_credit` AFTER UPDATE ON `takes` FOR EACH ROW BEGIN
	IF new.grade <> "F" and new.grade is not null and (old.grade = "F" or old.grade is null) THEN
		update student
		set total_credit = total_credit +
			(select credit
			from course
			where course_id = new.course_id)
		where student_id = new.student_id;
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `teaches`
--

DROP TABLE IF EXISTS `teaches`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teaches` (
  `professor_id` varchar(45) NOT NULL COMMENT '교수 아이디',
  `course_id` varchar(45) NOT NULL COMMENT '강의 아이디',
  `section_id` char(1) NOT NULL COMMENT '분반 아이디',
  `semester` varchar(45) NOT NULL COMMENT '학기',
  `year` varchar(10) NOT NULL COMMENT '년도',
  PRIMARY KEY (`professor_id`,`course_id`,`section_id`,`semester`,`year`),
  KEY `FK_Teaches_course_id_Section_course_id` (`course_id`,`section_id`,`semester`,`year`),
  CONSTRAINT `FK_Teaches_course_id_Section_course_id` FOREIGN KEY (`course_id`, `section_id`, `semester`, `year`) REFERENCES `section` (`course_id`, `section_id`, `semester`, `year`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_Teaches_professor_id_Professor_professor_id` FOREIGN KEY (`professor_id`) REFERENCES `professor` (`professor_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teaches`
--

LOCK TABLES `teaches` WRITE;
/*!40000 ALTER TABLE `teaches` DISABLE KEYS */;
INSERT INTO `teaches` VALUES ('2','1','가','Spring','2017'),('2','1','가','Spring','2018'),('2','1','가','Spring','2019'),('2','1','가','Spring','2020'),('6','11','가','Fall','2017'),('6','11','가','Spring','2019'),('6','11','가','Spring','2020'),('7','12','가','Fall','2019'),('7','12','나','Fall','2019'),('8','13','가','Spring','2019'),('8','13','나','Spring','2019'),('9','14','가','Fall','2018'),('10','15','가','Spring','2017'),('10','16','가','Spring','2018'),('1','2','가','Fall','2017'),('1','2','가','Fall','2018'),('1','2','나','Fall','2017'),('1','2','나','Fall','2018'),('11','21','가','Spring','2017'),('11','21','가','Spring','2019'),('11','21','가','Spring','2020'),('12','22','가','Fall','2019'),('12','22','나','Fall','2019'),('13','23','가','Spring','2019'),('13','23','나','Spring','2019'),('11','24','가','Fall','2018'),('14','25','가','Fall','2017'),('15','26','가','Spring','2018'),('3','3','가','Spring','2018'),('3','3','가','Spring','2019'),('3','3','나','Spring','2018'),('3','3','나','Spring','2019'),('4','4','가','Fall','2017'),('4','4','가','Fall','2018'),('3','4','가','Fall','2019'),('2','5','가','Fall','2017'),('2','5','가','Fall','2018'),('5','6','가','Fall','2017'),('5','6','가','Fall','2018'),('3','6','가','Fall','2019'),('3','7','가','Fall','2017'),('3','7','가','Fall','2019'),('3','7','가','Spring','2018'),('1','8','가','Spring','2018');
/*!40000 ALTER TABLE `teaches` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `computer_science_student`
--

/*!50001 DROP VIEW IF EXISTS `computer_science_student`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `computer_science_student` (`student_id`,`student_name`) AS select `student`.`student_id` AS `student_id`,`student`.`student_name` AS `student_name` from `student` where (`student`.`dept_name` = '컴퓨터학부') */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `dept_average_credit`
--

/*!50001 DROP VIEW IF EXISTS `dept_average_credit`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `dept_average_credit` (`dept_name`,`avg_credit`) AS select `student`.`dept_name` AS `dept_name`,(sum(if((`takes`.`grade` = 'F'),0,`course`.`credit`)) / count(distinct `student`.`student_id`)) AS `Name_exp_2` from ((`takes` left join `student` on((`takes`.`student_id` = `student`.`student_id`))) left join `course` on((`takes`.`course_id` = `course`.`course_id`))) group by `student`.`dept_name` */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `no_exist_advisor_student`
--

/*!50001 DROP VIEW IF EXISTS `no_exist_advisor_student`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `no_exist_advisor_student` (`student_id`,`student_name`) AS select `student`.`student_id` AS `student_id`,`student`.`student_name` AS `student_name` from `student` where `student`.`student_id` in (select `advisor`.`student_id` from `advisor`) is false */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `operating_system_professor`
--

/*!50001 DROP VIEW IF EXISTS `operating_system_professor`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `operating_system_professor` (`dept_name`,`professor_name`) AS select distinct `professor`.`dept_name` AS `dept_name`,`professor`.`professor_name` AS `professor_name` from ((`teaches` left join `professor` on((`teaches`.`professor_id` = `professor`.`professor_id`))) left join `course` on((`teaches`.`course_id` = `course`.`course_id`))) where (`course`.`title` = '운영체제') */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-12-14 13:18:36
