env = Environment()

cgen = env.Command('Core/CPU/Interpreter/Interpreter_inst.cgen', 'Core/Generators/InterpreterGen.py', 'python $SOURCE > /dev/null')
Depends(cgen, 'Core/Generators/opcodes.txt')

Program('interpreter', Glob('Core/CPU/Interpreter/*.cpp'))
