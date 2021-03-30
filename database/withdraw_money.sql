DELIMITER //
CREATE PROCEDURE withdraw_money(IN id INT, IN amount DOUBLE)
withdraw_money:BEGIN    
    SELECT account.id_account into @accid from account join card on account.id_account = card.id_account where id_card = id;
    SET @test = row_count();
    
    IF (@test = 0) THEN
        SELECT "Card does not have any accounts attached to it";
		LEAVE withdraw_money;
	END IF;
    
    IF (amount < 0) THEN
        SELECT "You cannot use this procedure to deposit any money";
        LEAVE withdraw_money;
        END IF;
    
      
	START transaction;
    UPDATE account SET balance=balance-amount WHERE id_account=@accid AND balance-amount>0;
    SET @test=row_count();
    IF(@test>0) THEN
		COMMIT;
			INSERT INTO account_action(id_account,amount,date,action_type) VALUES(@accid,amount,NOW(),'otto');
	ELSE
		ROLLBACK; 
	END IF;
END
//
DELIMITER ;
