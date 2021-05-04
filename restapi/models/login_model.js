const db = require('../database');

const login={
  checkPin: function(username, callback) {
      return db.query('SELECT pin, locked FROM card WHERE id_card = ?',[username], callback); 
    },

  isLocked: function(username, callback) {
      return db.query('SELECT locked FROM card WHERE id_card = ?',[username],callback);
  }
};


          
module.exports = login;
