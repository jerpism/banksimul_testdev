DELIMITER //
CREATE PROCEDURE money_action(IN id INT, IN amount DOUBLE)
money_action:BEGIN    
    SELECT account.id_account into @accid from account join card on account.id_account = card.id_account where id_card = id;
    SET @test = row_count();
    
    IF (@test = 0) THEN
		LEAVE money_action;
        SELECT "Card does not have any accounts attached to it";
	END IF;
      
	START transaction;
    UPDATE account SET balance=balance+amount WHERE id_account=@v1 AND balance+amount>0;
    SET @test=row_count();
    IF(@test>0) THEN
		COMMIT;
        IF(amount>0) THEN
			INSERT INTO account_action(id_account,amount,date,action_type) VALUES(@accid,amount,NOW(),'pano');
		ELSE
			INSERT INTO account_action(id_account,amount,date,action_type) VALUES(@accid,amount,NOW(),'otto');
		END IF;
	ELSE 
		ROLLBACK; 
	END IF;
END
//
DELIMITER ;
