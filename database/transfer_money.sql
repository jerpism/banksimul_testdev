DELIMITER //
-- HUOM!!! Tätä kutsuessasi id_senderiin menee lähettäjän KORTIN NUMERO, josta selvitetään siihen liitetty tili
-- Kun taas id_recipient kohtaan menee vastaanottajan TILINUMERO 
CREATE PROCEDURE transfer_money(IN id_sender INT, IN id_recipient INT, IN amount DOUBLE)
transfer_money:BEGIN
	-- Varmistetaan, että vastaanottajan tili on olemassa ja ei jatketa, jos ei.
    IF NOT EXISTS (select 1 FROM account where id_account = id_recipient) THEN
	SELECT "Recipient account does not exist";
    LEAVE transfer_money;
    END IF;
    
    -- Selvitetään lähettäjän tilinumero kortista
	SELECT account.id_account into @sender from account join card on account.id_account = card.id_account where id_card = id_sender;
    
    -- Poistutaan, jos yritetään siirtä negatiivisia summia rahaa.
    -- Tätä ei käytännössä pitäisi tapahtua ja jo ohjelman pitäisi estää se,
    -- mutta varmuuden vuoksi.
	IF(amount < 0) THEN
    SELECT "You cannot transfer negative amounts of money";
    LEAVE transfer_money;
    END IF;
    
    START transaction;
    UPDATE account SET balance=balance-amount WHERE id_account=@sender AND balance-amount>0;
    SET @test=row_count();
    IF(@test>0) THEN
		UPDATE account SET balance=balance+amount WHERE id_account=id_recipient;
        SET @test=row_count();
        
        IF(@test > 0) THEN
			COMMIT;
			-- Merkitään tapahtumat account_action -tauluun
			INSERT INTO account_action(id_account,amount,date,action_type) VALUES(@sender,-amount,NOW(),'siirto');
			INSERT INTO account_action(id_account,amount,date,action_type) VALUES(id_recipient,+amount,NOW(),'siirto');
        ELSE 
			ROLLBACK;
		END IF;
        
	ELSE 
		ROLLBACK; 
	END IF;
END
//
DELIMITER ;
