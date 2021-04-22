const db = require('../database');

const customer = {
    getName: function(id, callback){
        return db.query('select CONCAT(fname," ",lname) as fullname from customer join card on card.id_customer = customer.id_customer where id_card=? ', [id],callback);
    }
};

module.exports = customer;
