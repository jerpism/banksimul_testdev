const db = require('../database');

const customer = {
    getInfo: function(id, callback){
        return db.query('select CONCAT(fname," ",lname) as fullname, address, phone from customer join card on card.id_customer = customer.id_customer where id_card=? ', [id],callback);
    }
};

module.exports = customer;
