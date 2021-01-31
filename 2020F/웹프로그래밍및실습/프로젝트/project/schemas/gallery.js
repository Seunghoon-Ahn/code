const mongoose = require('mongoose');

const { Schema } = mongoose;
const { Types: { ObjectId } } = Schema;
const gallerySchema = new Schema({
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
  createdAt: {
    type: Date,
    default: Date.now,
  },
  img: {
    type: String,
    required: true,
  },
  hashtags: [{
    type: String,
  }],
});

module.exports = mongoose.model('gallery', gallerySchema);
