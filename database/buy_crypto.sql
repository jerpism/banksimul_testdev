DELIMITER //

CREATE PROCEDURE buy_crypto(IN id_acc INT, IN id_crypto INT, IN amount DOUBLE)
buy_crypto:BEGIN
	IF NOT EXISTS( select 1 FROM cryptoaccount where id_cryptoaccount = id_crypto) THEN
		SELECT "Your card does not have an account for cryptocurrency";
        LEAVE buy_crypto;
	END IF;

	IF(amount < 0) THEN
		SELECT "You cannot buy negative amounts of cryptocurrency";
        LEAVE buy_crypto;
	END IF;

 -- SELECT cryptoaccount.id_cryptoaccount INTO @cryptoacc FROM card JOIN cryptoaccount ON card.id_cryptoaccount = cryptoaccount.id_cryptoaccount WHERE id_card = cardid;
 --   SELECT account.id_account INTO @accid FROM card JOIN account ON card.id_account = account.id_account WHERE id_card = cardid;
 
	SELECT crypto INTO @rate FROM rates;

	START transaction;
    UPDATE account SET balance = balance-amount WHERE id_account = id_acc AND balance-amount > 0;
    SET @test=row_count();
    
    IF(@test > 0) THEN
		UPDATE cryptoaccount SET balance = balance+amount*@rate WHERE id_cryptoaccount = id_crypto;
        
        SET @test=row_count();
        
        IF(@test > 0) THEN
			COMMIT;
            INSERT INTO account_action(id_account,amount,date,action_type) VALUES(id_acc,-amount,NOW(),'Kryptovaluutan osto');
            INSERT INTO cryptoaccount_action (id_cryptoaccount,amount,date,action_type) VALUES(id_crypto,+amount*@rate,NOW(),'Kryptovaluutan osto');
		ELSE
			ROLLBACK;
            END IF;
		ELSE
			ROLLBACK;
		END IF;
END //
DELIMITER ;
