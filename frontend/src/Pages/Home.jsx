import { useState } from "react";
import { MdOutlineAdd } from "react-icons/md";
import { HiMinus } from "react-icons/hi";
import { RxCross2 } from "react-icons/rx";
import { HiMiniDivide } from "react-icons/hi2";
import axios from "axios";

export default function Home() {
    const [num1, setNum1] = useState("");
    const [num2, setNum2] = useState("");
    const [selectedOp, setSelectedOp] = useState("");
    const [result, setResult] = useState("");

    const ops = [
        { key: "add", Icon: MdOutlineAdd, border: "border-green-400", fill: "bg-green-400", text: "text-green-600" },
        { key: "sub", Icon: HiMinus, border: "border-yellow-400", fill: "bg-yellow-400", text: "text-yellow-600" },
        { key: "mul", Icon: RxCross2, border: "border-purple-400", fill: "bg-purple-400", text: "text-purple-600" },
        { key: "div", Icon: HiMiniDivide, border: "border-red-400", fill: "bg-red-400", text: "text-red-600" },
    ];

    const handleOperation = async () => {
        try {
            if (!selectedOp) {
                throw new Error("Please select an operator");
            }
            if (num1.trim() === "" || num2.trim() === "" || isNaN(num1) || isNaN(num2)) {
                throw new Error("Invalid Input");
            }
            
            const isFloat = num1.includes(".") || num2.includes(".");
            const n1 = isFloat ? parseFloat(num1) : parseInt(num1, 10);
            const n2 = isFloat ? parseFloat(num2) : parseInt(num2, 10);
            
            const body = {
                operand1: n1,
                operand2: n2,
                operation: selectedOp,
                type: isFloat ? "float" : "int",
            };
            
            const response = await axios.post("http://localhost:3079/arithm", body);
            
            setResult(response.data.result);
        } catch (err) {
            console.error(err);
            setResult(err.message || "Invalid Input");
        }
    };

    return (
        <div className="min-h-screen bg-gray-100 flex flex-col">
            <main className="flex-grow flex items-center justify-center p-6">
                <div className="w-full max-w-md bg-white rounded-2xl shadow-lg p-8">
                    <h2 className="text-xl font-medium mb-6 text-center">
                        Enter Two Numbers
                    </h2>

                    <input
                        type="text"
                        placeholder="First number"
                        value={num1}
                        onChange={(e) => setNum1(e.target.value)}
                        className="w-full mb-4 px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-400 transition"
                    />

                    <input
                        type="text"
                        placeholder="Second number"
                        value={num2}
                        onChange={(e) => setNum2(e.target.value)}
                        className="w-full mb-6 px-4 py-2 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-400 transition"
                    />
                    
                    <div className="flex justify-between space-x-4 mb-4">
                        {ops.map(({ key, Icon, border, fill, text }) => (
                            <button
                                key={key}
                                onClick={() => setSelectedOp(key)}
                                className={`
                flex-1 flex items-center justify-center p-3 rounded-lg shadow-md transition active:scale-95
                ${selectedOp === key
                                        ? `${fill} text-white`
                                        : `${border} ${text} hover:shadow-lg`}
                `}
                            >
                                <Icon className="text-2xl" />
                            </button>
                        ))}
                    </div>

                    {/* Calculate */}
                    <button
                        onClick={handleOperation}
                        className="w-full py-3 mb-6 bg-blue-500 text-white rounded-lg shadow-md hover:bg-blue-600 active:scale-95 transition"
                    >
                        Calculate
                    </button>

                    <div className="text-center">
                        <span className="text-gray-600">Result:</span>
                        <p className="mt-2 text-2xl font-semibold">{result}</p>
                    </div>
                </div>
            </main>
        </div>
    );
}
