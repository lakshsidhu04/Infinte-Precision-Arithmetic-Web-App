import { useState } from "react";

export default function Navbar() {
    const [isOpen, setIsOpen] = useState(false);

    return (
        <nav className="bg-white shadow-md">
            <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8">
                <div className="flex justify-between items-center h-16">
                    
                    <div className="flex-shrink-0">
                        <a href="/" className="text-2xl font-bold text-gray-800">
                            InfArithm
                        </a>
                    </div>
                    
                    <div className="hidden md:flex space-x-6">
                        <a href="#features" className="text-gray-600 hover:text-gray-900">
                            Features
                        </a>
                        <a href="#pricing" className="text-gray-600 hover:text-gray-900">
                            Pricing
                        </a>
                        <a href="#about" className="text-gray-600 hover:text-gray-900">
                            About
                        </a>
                        <a
                            href="#login"
                            className="px-4 py-2 bg-blue-600 text-white rounded hover:bg-blue-700"
                        >
                            Log In
                        </a>
                    </div>

                    {/* Mobile menu button */}
                    <div className="md:hidden">
                        <button
                            onClick={() => setIsOpen(!isOpen)}
                            type="button"
                            className="text-gray-800 hover:text-gray-900 focus:outline-none"
                        >
                            <svg
                                className="h-6 w-6"
                                fill="none"
                                stroke="currentColor"
                                viewBox="0 0 24 24"
                            >
                                {isOpen ? (
                                    <path
                                        strokeLinecap="round"
                                        strokeLinejoin="round"
                                        strokeWidth="2"
                                        d="M6 18L18 6M6 6l12 12"
                                    />
                                ) : (
                                    <path
                                        strokeLinecap="round"
                                        strokeLinejoin="round"
                                        strokeWidth="2"
                                        d="M4 6h16M4 12h16M4 18h16"
                                    />
                                )}
                            </svg>
                        </button>
                    </div>
                </div>
            </div>

            {/* Mobile Menu */}
            {isOpen && (
                <div className="md:hidden bg-white px-2 pt-2 pb-3 space-y-1">
                    <a
                        href="#features"
                        className="block px-3 py-2 rounded text-gray-700 hover:bg-gray-100"
                    >
                        Features
                    </a>
                    <a
                        href="#pricing"
                        className="block px-3 py-2 rounded text-gray-700 hover:bg-gray-100"
                    >
                        Pricing
                    </a>
                    <a
                        href="#about"
                        className="block px-3 py-2 rounded text-gray-700 hover:bg-gray-100"
                    >
                        About
                    </a>
                    <a
                        href="#login"
                        className="block px-3 py-2 mt-1 rounded bg-blue-600 text-white hover:bg-blue-700"
                    >
                        Log In
                    </a>
                </div>
            )}
        </nav>
    );
}
