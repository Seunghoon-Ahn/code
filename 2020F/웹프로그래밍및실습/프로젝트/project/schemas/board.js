const mongoose = require('mongoose');

const { Schema } = mongoose;
const { Types: { ObjectId } } = Schema;
const boardSchema = new Schema({
  title: {
    type: String,
    required: true,
  },
  commenterid: {
    type: ObjectId,
    required: true,
    ref: 'User',
  },
  commenter: {
    type: String,
    required: true,
    ref: 'User',
  },
  comment: {
    type: String,
    required: true,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
  hashtags: [{
    type: String,
  }],
});

module.exports = mongoose.model('board', boardSchema);
