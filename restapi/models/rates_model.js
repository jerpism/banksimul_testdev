const db=require('../database');

const rates={
    getRate: function(request, callback){
        return db.query('SELECT crypto FROM rates',callback);
    }
};

module.exports = rates;
