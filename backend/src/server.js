const express = require('express')
const cors = require('cors')
const arithmetic = require('./routes/Arithmetic')

const app = express()
app.use(cors())
app.use(express.json())

app.use('/arithm', arithmetic)

const PORT = process.env.PORT || 3079
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})
module.exports = app

