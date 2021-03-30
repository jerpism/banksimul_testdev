var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var actionsRouter = require('./routes/actions');
var cardRouter = require('./routes/card');

var app = express();
const basicAuth = require('express-basic-auth');
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(basicAuth({users: { 'admin': '1234'}}));

app.use('/actions', actionsRouter);
app.use('/card', cardRouter);

module.exports = app;

