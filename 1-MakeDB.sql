-- MySQL Script generated by MySQL Workbench
-- 04/20/15 04:20:00
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `mydb` ;

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`user` ;

CREATE TABLE IF NOT EXISTS `mydb`.`user` (
  `iduser` INT NOT NULL,
  `first_name` VARCHAR(20) NULL,
  `last_name` VARCHAR(25) NULL,
  `card_id` VARCHAR(8) NOT NULL,
  `date_hired` DATE NULL,
  PRIMARY KEY (`iduser`, `card_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`log`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`log` ;

CREATE TABLE IF NOT EXISTS `mydb`.`log` (
  `timestamp` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `card_id` VARCHAR(8) NOT NULL,
  PRIMARY KEY (`timestamp`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
