import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
import Navbar from './Components/Navbar'
import { BrowserRouter, Routes, Route, Link } from "react-router-dom";
import Home from './Pages/Home'

function App() {
  const [count, setCount] = useState(0)

  return (
    <>
      <Navbar />
      {/* router setup */}
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Home/>}/>
          {/* <Route path="/about" element={<h1>About Page</h1>} />
          <Route path="/features" element={<h1>Features Page</h1>} />
          <Route path="/pricing" element={<h1>Pricing Page</h1>} />
          <Route path="/login" element={<h1>Login Page</h1>} /> */}
        </Routes>
      </BrowserRouter>
    </>
  )
}

export default App
