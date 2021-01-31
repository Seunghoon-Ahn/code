-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: localhost    Database: DB20162481
-- ------------------------------------------------------
-- Server version	8.0.22

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
  `student_id` varchar(45) NOT NULL,
  `professor_id` varchar(45) NOT NULL,
  PRIMARY KEY (`student_id`,`professor_id`),
  KEY `professor_id` (`professor_id`),
  CONSTRAINT `advisor_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `student` (`student_id`),
  CONSTRAINT `advisor_ibfk_2` FOREIGN KEY (`professor_id`) REFERENCES `professor` (`professor_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `advisor`
--

LOCK TABLES `advisor` WRITE;
/*!40000 ALTER TABLE `advisor` DISABLE KEYS */;
INSERT INTO `advisor` VALUES ('20152001','2006206'),('20182002','2006206'),('20151001','2008101'),('20171005','2008101'),('20151002','2008103'),('20151003','2008103'),('20153001','2008301'),('20153002','2008301'),('20183003','2008302'),('20172006','2009203'),('20172008','2009203'),('20161046','2010101'),('20161030','2010102'),('20152002','2010201'),('20162014','2010201'),('20163021','2010303'),('20183065','2010303'),('20162032','2011201'),('20173001','2012307'),('20161001','2013101'),('20181027','2013101'),('20162029','2014201'),('20163007','2014304'),('20173048','2014304');
/*!40000 ALTER TABLE `advisor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `course`
--

DROP TABLE IF EXISTS `course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `course` (
  `course_id` varchar(45) NOT NULL,
  `title` varchar(45) DEFAULT NULL,
  `dept_name` varchar(45) DEFAULT NULL,
  `credit` int DEFAULT NULL,
  PRIMARY KEY (`course_id`),
  KEY `dept_name` (`dept_name`),
  CONSTRAINT `course_ibfk_1` FOREIGN KEY (`dept_name`) REFERENCES `department` (`dept_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `course`
--

LOCK TABLES `course` WRITE;
/*!40000 ALTER TABLE `course` DISABLE KEYS */;
INSERT INTO `course` VALUES ('101','자료구조','컴퓨터학부',3),('102','운영체제','컴퓨터학부',3),('103','데이터베이스','컴퓨터학부',3),('104','파일처리','컴퓨터학부',3),('105','알고리즘','컴퓨터학부',2),('106','정보보안','컴퓨터학부',1),('107','프로그래밍','컴퓨터학부',3),('108','리눅스시스템프로그래밍','컴퓨터학부',3),('201','자료구조','미디어학부',3),('202','운영체제','미디어학부',3),('203','데이터베이스','미디어학부',3),('205','알고리즘','미디어학부',2),('207','프로그래밍','미디어학부',3),('208','리눅스시스템프로그래밍','미디어학부',3),('301','자료구조','소프트웨어학부',3),('302','운영체제','소프트웨어학부',3),('303','데이터베이스','소프트웨어학부',3),('305','알고리즘','소프트웨어학부',2),('307','프로그래밍','소프트웨어학부',3),('308','리눅스시스템프로그레밍','소프트웨어학부',3);
/*!40000 ALTER TABLE `course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `department`
--

DROP TABLE IF EXISTS `department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `department` (
  `dept_name` varchar(45) NOT NULL,
  `budget` int DEFAULT NULL,
  PRIMARY KEY (`dept_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `department`
--

LOCK TABLES `department` WRITE;
/*!40000 ALTER TABLE `department` DISABLE KEYS */;
INSERT INTO `department` VALUES ('미디어학부',220),('소프트웨어학부',150),('컴퓨터학부',300);
/*!40000 ALTER TABLE `department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `prereq`
--

DROP TABLE IF EXISTS `prereq`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `prereq` (
  `course_id` varchar(45) NOT NULL,
  `prereq_id` varchar(45) NOT NULL,
  PRIMARY KEY (`course_id`,`prereq_id`),
  KEY `prereq_id` (`prereq_id`),
  CONSTRAINT `prereq_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `course` (`course_id`),
  CONSTRAINT `prereq_ibfk_2` FOREIGN KEY (`prereq_id`) REFERENCES `course` (`course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prereq`
--

LOCK TABLES `prereq` WRITE;
/*!40000 ALTER TABLE `prereq` DISABLE KEYS */;
INSERT INTO `prereq` VALUES ('105','101'),('101','107'),('205','201'),('201','207'),('305','301'),('301','307');
/*!40000 ALTER TABLE `prereq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `professor`
--

DROP TABLE IF EXISTS `professor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `professor` (
  `professor_id` varchar(45) NOT NULL,
  `professor_name` varchar(45) DEFAULT NULL,
  `dept_name` varchar(45) DEFAULT NULL,
  `salary` int DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  PRIMARY KEY (`professor_id`),
  KEY `dept_name` (`dept_name`),
  CONSTRAINT `professor_ibfk_1` FOREIGN KEY (`dept_name`) REFERENCES `department` (`dept_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `professor`
--

LOCK TABLES `professor` WRITE;
/*!40000 ALTER TABLE `professor` DISABLE KEYS */;
INSERT INTO `professor` VALUES ('2006206','최장수','미디어학부',90,'2006-03-01'),('2008101','나현숙','컴퓨터학부',75,'2008-03-01'),('2008103','홍지만','컴퓨터학부',64,'2008-03-01'),('2008301','정민기','소프트웨어학부',50,'2008-03-01'),('2008302','장도리','소프트웨어학부',70,'2008-03-01'),('2009203','정미디','미디어학부',64,'2009-03-01'),('2010101','김철수','컴퓨터학부',100,'2010-03-01'),('2010102','이순신','컴퓨터학부',50,'2010-03-01'),('2010201','김코딩','미디어학부',100,'2010-03-01'),('2010202','박나루','미디어학부',50,'2010-03-01'),('2010303','하기스','소프트웨어학부',100,'2010-03-01'),('2011101','박동주','컴퓨터학부',80,'2011-03-01'),('2011201','황정현','미디어학부',78,'2011-03-01'),('2011301','이진욱','소프트웨어학부',65,'2011-03-01'),('2012307','오만원','소프트웨어학부',87,'2012-03-01'),('2013101','최봉준','컴퓨터학부',87,'2013-03-01'),('2014201','신정수','미디어학부',87,'2014-03-01'),('2014304','장대호','소프트웨어학부',90,'2014-03-01');
/*!40000 ALTER TABLE `professor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `section`
--

DROP TABLE IF EXISTS `section`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `section` (
  `course_id` varchar(45) NOT NULL,
  `section_id` varchar(45) NOT NULL,
  `semester` char(30) NOT NULL,
  `year` varchar(45) NOT NULL,
  PRIMARY KEY (`course_id`,`section_id`,`semester`,`year`),
  CONSTRAINT `section_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `course` (`course_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `section`
--

LOCK TABLES `section` WRITE;
/*!40000 ALTER TABLE `section` DISABLE KEYS */;
INSERT INTO `section` VALUES ('101','가','Spring','2017'),('101','가','Spring','2018'),('101','가','Spring','2019'),('101','가','Spring','2020'),('102','가','Fall','2017'),('102','가','Fall','2018'),('102','가','Fall','2019'),('102','나','Fall','2017'),('102','나','Fall','2018'),('102','나','Fall','2019'),('103','가','Spring','2018'),('103','나','Spring','2018'),('104','가','Fall','2019'),('104','가','Spring','2017'),('104','가','Spring','2018'),('104','가','Spring','2020'),('105','가','Fall','2017'),('105','가','Fall','2020'),('105','가','Spring','2018'),('106','가','Fall','2017'),('106','가','Fall','2018'),('106','가','Fall','2020'),('107','가','Fall','2017'),('107','가','Fall','2018'),('107','가','Spring','2019'),('108','가','Spring','2017'),('108','가','Spring','2018'),('201','가','Fall','2019'),('201','가','Spring','2017'),('201','가','Spring','2018'),('201','가','Spring','2019'),('201','가','Spring','2020'),('202','가','Fall','2017'),('202','가','Fall','2018'),('202','나','Fall','2017'),('202','나','Fall','2018'),('203','가','Spring','2020'),('203','나','Spring','2020'),('205','가','Fall','2017'),('205','가','Fall','2019'),('205','가','Fall','2020'),('205','가','Spring','2018'),('207','가','Fall','2020'),('207','가','Spring','2017'),('207','가','Spring','2019'),('208','가','Spring','2018'),('208','가','Spring','2019'),('301','가','Fall','2019'),('301','가','Spring','2017'),('301','가','Spring','2018'),('301','가','Spring','2019'),('301','가','Spring','2020'),('302','가','Fall','2018'),('302','가','Fall','2020'),('302','나','Fall','2018'),('302','나','Fall','2020'),('303','가','Spring','2019'),('303','나','Spring','2019'),('305','가','Fall','2017'),('305','가','Spring','2018'),('305','가','Spring','2020'),('307','가','Fall','2017'),('307','가','Fall','2018'),('307','가','Fall','2019'),('307','가','Fall','2020'),('307','가','Spring','2019'),('308','가','Spring','2017'),('308','가','Spring','2018'),('308','가','Spring','2019');
/*!40000 ALTER TABLE `section` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `student` (
  `student_id` varchar(45) NOT NULL,
  `student_name` varchar(45) DEFAULT NULL,
  `dept_name` varchar(45) DEFAULT NULL,
  `admission_date` date DEFAULT NULL,
  `home_address` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`student_id`),
  KEY `dept_name` (`dept_name`),
  CONSTRAINT `student_ibfk_1` FOREIGN KEY (`dept_name`) REFERENCES `department` (`dept_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('20151001','김준수','컴퓨터학부','2015-03-01','인천'),('20151002','박진우','컴퓨터학부','2015-03-01','서울'),('20151003','최동화','컴퓨터학부','2015-03-01','대구'),('20152001','김홍기','미디어학부','2015-03-01','인천'),('20152002','전동차','미디어학부','2015-03-01','부산'),('20153001','김범수','소프트웨어학부','2015-03-01','서울'),('20153002','강동원','소프트웨어학부','2015-03-01','부산'),('20161001','안승훈','컴퓨터학부','2016-03-01','서울'),('20161030','나윤경','컴퓨터학부','2016-03-01','부산'),('20161046','홍길동','컴퓨터학부','2016-03-01','대전'),('20162014','조민영','미디어학부','2016-03-01','대전'),('20162029','박소은','미디어학부','2016-03-01','대구'),('20162032','심봉사','미디어학부','2016-03-01','부산'),('20163007','최재인','소프트웨어학부','2016-03-01','대전'),('20163021','박예진','소프트웨어학부','2016-03-01','서울'),('20171005','황정현','컴퓨터학부','2017-03-01','청주'),('20172006','이선화','미디어학부','2017-03-01','서울'),('20172008','황정국','미디어학부','2017-03-01',NULL),('20173001','이시국','소프트웨어학부','2017-03-01','대구'),('20173048','박나래','소프트웨어학부','2017-03-01','광주'),('20181027','조동휘','컴퓨터학부','2018-03-01','광주'),('20182002','전대호','미디어학부','2018-03-01','서울'),('20183003','손담비','소프트웨어학부','2018-03-01','서울'),('20183065','마지막','소프트웨어학부','2018-03-01','부산');
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `takes`
--

DROP TABLE IF EXISTS `takes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `takes` (
  `student_id` varchar(45) NOT NULL,
  `course_id` varchar(45) NOT NULL,
  `section_id` varchar(45) NOT NULL,
  `semester` char(30) NOT NULL,
  `year` varchar(45) NOT NULL,
  `grade` char(10) DEFAULT NULL,
  PRIMARY KEY (`student_id`,`course_id`,`section_id`,`semester`,`year`),
  KEY `course_id` (`course_id`,`section_id`,`semester`,`year`),
  CONSTRAINT `takes_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `student` (`student_id`),
  CONSTRAINT `takes_ibfk_2` FOREIGN KEY (`course_id`, `section_id`, `semester`, `year`) REFERENCES `section` (`course_id`, `section_id`, `semester`, `year`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `takes`
--

LOCK TABLES `takes` WRITE;
/*!40000 ALTER TABLE `takes` DISABLE KEYS */;
INSERT INTO `takes` VALUES ('20151001','101','가','Spring','2020','D'),('20151001','102','가','Fall','2017','A'),('20151001','103','가','Spring','2018','A'),('20151001','104','가','Spring','2017','B'),('20151001','105','가','Fall','2020','F'),('20151001','106','가','Fall','2017','B'),('20151001','107','가','Spring','2019','A'),('20151001','108','가','Spring','2017','C'),('20151002','101','가','Spring','2018','A'),('20151002','102','나','Fall','2017','A'),('20151002','103','가','Spring','2018','A'),('20151002','104','가','Fall','2019','A'),('20151002','105','가','Fall','2020','A'),('20151002','106','가','Fall','2017','A'),('20151002','107','가','Fall','2017','A'),('20151003','101','가','Spring','2020','C'),('20151003','102','나','Fall','2018','B'),('20151003','103','나','Spring','2018','A'),('20151003','104','가','Spring','2017','C'),('20151003','105','가','Fall','2020','B'),('20151003','106','가','Fall','2017','D'),('20151003','107','가','Spring','2019','D'),('20152001','201','가','Spring','2018','B'),('20152001','202','나','Fall','2017','C'),('20152001','203','가','Spring','2020','B'),('20152001','205','가','Fall','2019','A'),('20152001','207','가','Spring','2017','A'),('20152001','208','가','Spring','2019','B'),('20152002','201','가','Spring','2019','A'),('20152002','202','가','Fall','2017','A'),('20152002','205','가','Fall','2019','A'),('20152002','207','가','Spring','2017','A'),('20152002','208','가','Spring','2018','A'),('20153001','301','가','Spring','2018','A'),('20153001','302','나','Fall','2018','B'),('20153001','303','가','Spring','2019','C'),('20153001','305','가','Spring','2020','A'),('20153001','307','가','Fall','2017','C'),('20153001','308','가','Spring','2017','B'),('20153002','301','가','Spring','2018','A'),('20153002','302','가','Fall','2018','B'),('20153002','303','나','Spring','2019','A'),('20153002','305','가','Spring','2020','A'),('20153002','307','가','Fall','2017','A'),('20153002','308','가','Spring','2017','A'),('20161001','101','가','Spring','2018','A'),('20161001','103','가','Spring','2018','A'),('20161001','104','가','Spring','2017','A'),('20161001','105','가','Fall','2020','A'),('20161001','106','가','Fall','2020','A'),('20161001','107','가','Fall','2017','A'),('20161030','102','나','Fall','2018','A'),('20161030','103','가','Spring','2018','B'),('20161030','104','가','Spring','2020','B'),('20161030','106','가','Fall','2017','A'),('20161030','108','가','Spring','2017','B'),('20161046','101','가','Spring','2020','B'),('20161046','102','가','Fall','2019','B'),('20161046','104','가','Fall','2019','D'),('20161046','105','가','Fall','2020','C'),('20161046','107','가','Spring','2019','B'),('20162014','201','가','Fall','2019','B'),('20162014','202','나','Fall','2018','A'),('20162014','203','나','Spring','2020','D'),('20162014','207','가','Spring','2019','C'),('20162014','208','가','Spring','2018','A'),('20162029','201','가','Fall','2019','B'),('20162029','202','가','Fall','2018','A'),('20162029','203','가','Spring','2020','C'),('20162029','207','가','Spring','2019','C'),('20162029','208','가','Spring','2018','F'),('20162032','201','가','Fall','2019','A'),('20162032','202','가','Fall','2017','A'),('20162032','205','가','Fall','2020','A'),('20162032','207','가','Spring','2019','B'),('20162032','208','가','Spring','2018','C'),('20163007','301','가','Spring','2018','A'),('20163007','302','나','Fall','2020','C'),('20163007','305','가','Spring','2020','A'),('20163007','307','가','Fall','2017','A'),('20163021','301','가','Fall','2019','B'),('20163021','303','가','Spring','2019','C'),('20163021','307','가','Spring','2019','A'),('20163021','308','가','Spring','2019','C'),('20171005','101','가','Spring','2020','A'),('20171005','102','가','Fall','2019','B'),('20171005','104','가','Fall','2019','C'),('20171005','105','가','Fall','2020','D'),('20171005','107','가','Spring','2019','A'),('20172006','202','나','Fall','2017','B'),('20172006','203','나','Spring','2020','A'),('20172006','207','가','Fall','2020','A'),('20172006','208','가','Spring','2018','F'),('20172008','202','가','Fall','2017','D'),('20172008','207','가','Spring','2017','D'),('20173001','301','가','Spring','2020','A'),('20173001','302','나','Fall','2020','B'),('20173001','307','가','Fall','2017','C'),('20173001','308','가','Spring','2017','D'),('20173048','301','가','Fall','2019','B'),('20173048','303','가','Spring','2019','C'),('20173048','307','가','Fall','2017','B'),('20173048','308','가','Spring','2017','A'),('20181027','102','가','Fall','2018','B'),('20181027','103','가','Spring','2018','B'),('20181027','104','가','Spring','2020','A'),('20181027','106','가','Fall','2018','C'),('20181027','108','가','Spring','2018','D'),('20183003','302','가','Fall','2018','F'),('20183003','303','가','Spring','2019','C'),('20183003','307','가','Fall','2019','B'),('20183003','308','가','Spring','2018','A'),('20183065','301','가','Fall','2019','A'),('20183065','302','나','Fall','2020','D'),('20183065','305','가','Spring','2020','B'),('20183065','307','가','Spring','2019','B'),('20183065','308','가','Spring','2018','C');
/*!40000 ALTER TABLE `takes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `teaches`
--

DROP TABLE IF EXISTS `teaches`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `teaches` (
  `professor_id` varchar(45) NOT NULL,
  `course_id` varchar(45) NOT NULL,
  `section_id` varchar(45) NOT NULL,
  `semester` char(30) NOT NULL,
  `year` varchar(45) NOT NULL,
  PRIMARY KEY (`professor_id`,`course_id`,`section_id`,`semester`,`year`),
  KEY `course_id` (`course_id`,`section_id`,`semester`,`year`),
  CONSTRAINT `teaches_ibfk_1` FOREIGN KEY (`professor_id`) REFERENCES `professor` (`professor_id`),
  CONSTRAINT `teaches_ibfk_2` FOREIGN KEY (`course_id`, `section_id`, `semester`, `year`) REFERENCES `section` (`course_id`, `section_id`, `semester`, `year`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `teaches`
--

LOCK TABLES `teaches` WRITE;
/*!40000 ALTER TABLE `teaches` DISABLE KEYS */;
INSERT INTO `teaches` VALUES ('2011101','101','가','Spring','2017'),('2011101','101','가','Spring','2018'),('2011101','101','가','Spring','2019'),('2011101','101','가','Spring','2020'),('2008103','102','가','Fall','2017'),('2008103','102','가','Fall','2018'),('2008103','102','가','Fall','2019'),('2008103','102','나','Fall','2017'),('2008103','102','나','Fall','2018'),('2008103','102','나','Fall','2019'),('2010101','103','가','Spring','2018'),('2010101','103','나','Spring','2018'),('2008103','104','가','Fall','2019'),('2008101','104','가','Spring','2017'),('2008101','104','가','Spring','2018'),('2008101','104','가','Spring','2020'),('2010101','105','가','Fall','2017'),('2008101','105','가','Fall','2020'),('2010102','105','가','Spring','2018'),('2010101','106','가','Fall','2017'),('2013101','106','가','Fall','2018'),('2010102','106','가','Fall','2020'),('2010102','107','가','Fall','2017'),('2010102','107','가','Fall','2018'),('2008101','107','가','Spring','2019'),('2008103','108','가','Spring','2017'),('2008103','108','가','Spring','2018'),('2006206','201','가','Fall','2019'),('2010202','201','가','Spring','2017'),('2009203','201','가','Spring','2018'),('2014201','201','가','Spring','2019'),('2011201','201','가','Spring','2020'),('2006206','202','가','Fall','2017'),('2011201','202','가','Fall','2018'),('2006206','202','나','Fall','2017'),('2011201','202','나','Fall','2018'),('2014201','203','가','Spring','2020'),('2014201','203','나','Spring','2020'),('2010201','205','가','Fall','2017'),('2010201','205','가','Fall','2019'),('2010202','205','가','Fall','2020'),('2011201','205','가','Spring','2018'),('2010201','207','가','Fall','2020'),('2011201','207','가','Spring','2017'),('2009203','207','가','Spring','2019'),('2006206','208','가','Spring','2018'),('2010201','208','가','Spring','2019'),('2008301','301','가','Fall','2019'),('2008301','301','가','Spring','2017'),('2008301','301','가','Spring','2018'),('2008301','301','가','Spring','2019'),('2008301','301','가','Spring','2020'),('2008302','302','가','Fall','2018'),('2011301','302','가','Fall','2020'),('2008302','302','나','Fall','2018'),('2011301','302','나','Fall','2020'),('2008302','303','가','Spring','2019'),('2008302','303','나','Spring','2019'),('2008301','305','가','Fall','2017'),('2008301','305','가','Spring','2018'),('2008301','305','가','Spring','2020'),('2011301','307','가','Fall','2017'),('2012307','307','가','Fall','2018'),('2011301','307','가','Fall','2019'),('2014304','307','가','Fall','2020'),('2010303','307','가','Spring','2019'),('2010303','308','가','Spring','2017'),('2014304','308','가','Spring','2018'),('2011301','308','가','Spring','2019');
/*!40000 ALTER TABLE `teaches` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-11-10 21:47:05
