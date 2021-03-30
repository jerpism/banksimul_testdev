const db = require('../database');

const login={
  checkPin: function(username, callback) {
      return db.query('SELECT pin FROM card WHERE id_card = ?',[username], callback); 
    }
};
          
module.exports = login;
