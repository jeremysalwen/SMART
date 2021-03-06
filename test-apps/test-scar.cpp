/**
 *  Copyright 2010 by Benjamin J. Land (a.k.a. BenLand100)
 *
 *  This file is part of the SMART Minimizing Autoing Resource Thing (SMART)
 *
 *  SMART is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SMART is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SMART. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <windows.h>

using namespace std;

typedef long (*GetFunctionCount) (void) __attribute__((stdcall));
typedef long (*GetFunctionInfo)(int, void*&, char*&) __attribute__((stdcall));
typedef void (*Setup)(char*,char*,long,long,char*) __attribute__((stdcall));

int main(int argc, char** argv) {
    HMODULE libsmart = LoadLibrary("./Embedded_SMART.dll");
    cout << "Library: " << libsmart << '\n';
    cout << "GetFunctionCount: " << (void*)GetProcAddress(libsmart, "GetFunctionCount") << '\n';
    cout << "GetFunctionInfo: " << (void*)GetProcAddress(libsmart, "GetFunctionInfo") << '\n';
    GetFunctionCount count = (GetFunctionCount) GetProcAddress(libsmart, "GetFunctionCount");
    GetFunctionInfo info = (GetFunctionInfo) GetProcAddress(libsmart, "GetFunctionInfo");

    int exports = count();
    cout << "#Exports = " << count() << '\n';
    for (int i = 0; i < exports; i++) {
        char* def = new char[1024];
        void* addr;
        info(i,addr,def);
        cout << '\t' << addr << " = " << def  << '\n';
        delete def;
    }
    cout << "Starting SMART...\n";
    Setup setup = (Setup) GetProcAddress(libsmart, "std_setup");
    setup((char*)"http://world19.runescape.com/", (char*)",f5", 765, 503,(char*)"");

    while (true) Sleep(1000);

    FreeLibrary(libsmart);

    return 0;
}

