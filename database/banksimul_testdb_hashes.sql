-- MariaDB dump 10.19  Distrib 10.5.9-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: banksimul_testdb
-- ------------------------------------------------------
-- Server version	10.5.9-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account` (
  `id_account` int(11) NOT NULL,
  `balance` double DEFAULT NULL,
  PRIMARY KEY (`id_account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,9170),(2,3530.75);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_action`
--

DROP TABLE IF EXISTS `account_action`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `account_action` (
  `id_action` int(11) NOT NULL AUTO_INCREMENT,
  `id_account` int(11) NOT NULL,
  `amount` double DEFAULT NULL,
  `date` datetime DEFAULT NULL,
  `action_type` varchar(45) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id_action`),
  KEY `account_action_idx` (`id_account`),
  CONSTRAINT `account_action` FOREIGN KEY (`id_account`) REFERENCES `account` (`id_account`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=44 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_action`
--

LOCK TABLES `account_action` WRITE;
/*!40000 ALTER TABLE `account_action` DISABLE KEYS */;
INSERT INTO `account_action` VALUES (1,2,2000,'2021-03-29 19:55:13','pano'),(2,2,-2500,'2021-03-29 19:55:29','otto'),(3,2,6900.75,'2021-03-29 20:06:49','pano'),(4,2,-6900.75,'2021-03-29 20:06:59','otto'),(5,2,-6900,'2021-03-29 20:07:10','otto'),(6,2,300,'2021-03-30 11:31:54','pano'),(7,1,200,'2021-03-30 11:40:16','pano'),(8,2,300,'2021-03-30 11:48:50','pano'),(9,2,300,'2021-03-30 11:48:58','pano'),(10,2,300,'2021-03-30 11:52:24','pano'),(11,2,300,'2021-03-30 11:52:57','pano'),(12,1,200,'2021-03-30 11:56:26','pano'),(13,1,300,'2021-03-30 11:56:32','pano'),(14,1,300,'2021-03-30 11:56:48','pano'),(15,2,300,'2021-03-30 11:57:21','pano'),(16,2,300,'2021-03-30 11:57:46','pano'),(17,1,300,'2021-03-30 11:58:01','pano'),(18,2,300,'2021-03-30 11:58:54','otto'),(19,1,-200,'2021-03-30 12:43:19','siirto'),(20,2,200,'2021-03-30 12:43:19','siirto'),(21,1,-2400,'2021-03-30 13:07:24','siirto'),(22,2,2400,'2021-03-30 13:07:24','siirto'),(23,2,-200,'2021-03-30 13:19:14','siirto'),(24,1,200,'2021-03-30 13:19:14','siirto'),(25,2,-200,'2021-03-30 13:27:57','siirto'),(26,1,200,'2021-03-30 13:27:57','siirto'),(27,1,-100,'2021-03-30 13:34:54','siirto'),(28,2,100,'2021-03-30 13:34:54','siirto'),(29,1,-100,'2021-03-30 13:35:15','siirto'),(30,2,100,'2021-03-30 13:35:15','siirto'),(31,1,-100,'2021-03-30 17:36:07','siirto'),(32,2,100,'2021-03-30 17:36:07','siirto'),(33,1,200,'2021-03-31 10:19:39','otto'),(34,1,-200,'2021-03-31 10:20:40','siirto'),(35,2,200,'2021-03-31 10:20:40','siirto'),(36,1,-200,'2021-03-31 11:44:59','siirto'),(37,2,200,'2021-03-31 11:44:59','siirto'),(38,2,200,'2021-04-01 17:12:03','otto'),(39,1,200,'2021-04-01 17:12:16','otto'),(40,2,200,'2021-04-01 17:12:18','otto'),(41,2,200,'2021-04-01 17:12:21','otto'),(42,1,-30,'2021-04-06 19:43:57','siirto'),(43,2,30,'2021-04-06 19:43:57','siirto');
/*!40000 ALTER TABLE `account_action` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `card` (
  `id_card` int(11) NOT NULL,
  `id_customer` int(11) NOT NULL,
  `id_account` int(11) NOT NULL,
  `id_cryptoaccount` int(11) DEFAULT NULL,
  `pin` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id_card`,`id_customer`,`id_account`),
  KEY `customer_card_idx` (`id_customer`),
  KEY `card_account_idx` (`id_account`),
  KEY `card_cryptoaccount_idx` (`id_cryptoaccount`),
  CONSTRAINT `card_account` FOREIGN KEY (`id_account`) REFERENCES `account` (`id_account`) ON UPDATE CASCADE,
  CONSTRAINT `card_cryptoaccount` FOREIGN KEY (`id_cryptoaccount`) REFERENCES `cryptoaccount` (`id_cryptoaccount`) ON UPDATE CASCADE,
  CONSTRAINT `customer_card` FOREIGN KEY (`id_customer`) REFERENCES `customer` (`id_customer`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (1,1,1,NULL,'$2y$10$oQm0JKY7nEADnz0uANlw8OkeSlsj6QAGWHFiMGDjzcjfD3I7TnLP2'),(2,2,2,NULL,'$2y$10$OmnEHTo9VcZl.Dmrjd.kPO8gL.HPgWdsUTmzI6rMrwKy61HmY.HZK'),(3,3,2,NULL,'$2y$10$k4eOHpgFfWVduDGRzYrr/evOOHTi4AUx4J6//OMPDxbXd4Au9ETVi');
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cryptoaccount`
--

DROP TABLE IF EXISTS `cryptoaccount`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cryptoaccount` (
  `id_cryptoaccount` int(11) NOT NULL,
  `balance` double DEFAULT NULL,
  PRIMARY KEY (`id_cryptoaccount`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cryptoaccount`
--

LOCK TABLES `cryptoaccount` WRITE;
/*!40000 ALTER TABLE `cryptoaccount` DISABLE KEYS */;
INSERT INTO `cryptoaccount` VALUES (1,0.0576);
/*!40000 ALTER TABLE `cryptoaccount` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cryptoaccount_action`
--

DROP TABLE IF EXISTS `cryptoaccount_action`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cryptoaccount_action` (
  `id_action` int(11) NOT NULL AUTO_INCREMENT,
  `id_cryptoaccount` int(11) NOT NULL,
  `amount` double DEFAULT NULL,
  `date` datetime DEFAULT NULL,
  `action_type` varchar(45) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id_action`),
  KEY `cryptoaccount_action_idx` (`id_cryptoaccount`),
  CONSTRAINT `cryptoaccount_action` FOREIGN KEY (`id_cryptoaccount`) REFERENCES `cryptoaccount` (`id_cryptoaccount`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cryptoaccount_action`
--

LOCK TABLES `cryptoaccount_action` WRITE;
/*!40000 ALTER TABLE `cryptoaccount_action` DISABLE KEYS */;
/*!40000 ALTER TABLE `cryptoaccount_action` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `customer` (
  `id_customer` int(11) NOT NULL,
  `fname` varchar(45) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `lname` varchar(45) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `address` varchar(45) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `phone` varchar(45) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id_customer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Teppo','Testi','Oulukatu 3',NULL),(2,'Matti','Testi','Oulukatu 4',NULL),(3,'Mervi','Testi','Oulukatu 4',NULL);
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-04-07 14:54:37
