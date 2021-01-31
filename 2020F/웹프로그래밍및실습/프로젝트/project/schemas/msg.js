const mongoose = require('mongoose');

const { Schema } = mongoose;
//const { Types: { ObjectId } } = Schema;
const messageSchema = new Schema({
  sender: {
    type: String,
    required: true,
    ref: 'User',
  },
  receiver: {
    type: String,
    required: true,
    ref: 'User',
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
  content: {
    type: String,
    required: true,
  },
});

module.exports = mongoose.model('message', messageSchema);
