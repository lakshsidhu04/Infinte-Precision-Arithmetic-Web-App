const express = require('express')
const {spawn} = require('child_process')
const router = express.Router()
const path = require('path')
router.post('/', (req,res)=>{
    console.log("Received request for arithmetic operation")
    const body = req.body
    const type = body.type
    const oper = body.operation
    const operand1 = body.operand1
    const operand2 = body.operand2
    const exePath = path.join(__dirname, '../../cpp/my_inf_arith'); 
    const child = spawn(exePath,[type,oper,operand1,operand2])
    let output = ''
    child.stdout.on('data',(data)=>{
        output += data.toString()
    })

    child.on('close',()=>{
        res.json({
            result: output.trim()
        })
    })
})

module.exports = router