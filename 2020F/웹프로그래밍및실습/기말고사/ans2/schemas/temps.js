const mongoose = require('mongoose');

const { Schema } = mongoose;
const weatherSchema = new Schema({
  date: {
    type: String,
    required: true,
  },
  min: {
    type: Number,
    required: true,
  },
  max: {
    type: Number,
    required: true,
  },
});

module.exports = mongoose.model('temps', weatherSchema);
