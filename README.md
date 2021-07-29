# EMS-aircraft
Energy Management System of an aircraft powered by FC/PV/BATT/SC systems.
<hr/>

## Simulink
The simulink powertrain file ("Main/powertrain.slx") is composed of 5 parts to improve the understanding:
### Powertrain
<ul>
  <li>This part is defined as the Power architecture.</li>
  <li>It is composed of a FC system, a Battery system, a PV panel, a Supercapcitor, a Load and their respective converters.</li>
  <li>The converters are saved and locked in the "Lib/lib_converter.slx" file. There are composed of an average-based model converter and their regulators.</li>
</ul>
![image](https://user-images.githubusercontent.com/48295514/127478335-0b4b1bec-a9c8-4f56-86cc-27f6f06f7344.png)

### Inputs
<ul>
  <li>This part define the different inputs data needed to allow the simulation operation.</li>
  <li>It is composed of a block that allow the user yo chose different type of flights, the wanted bus voltage and the different solar irradiance and temperature variations.</li>
</ul>
![image](https://user-images.githubusercontent.com/48295514/127478481-d7866a50-621b-4c26-a565-43a942a38cc2.png)

### Energy Management System
<ul>
  <li>This part is the management controller. It enables the user to choose the energy management strategy for the current simulation.</li>
  <li>You can also choose to activate a power system or not.</li>
</ul>
![image](https://user-images.githubusercontent.com/48295514/127478545-f2687694-d744-4c7e-af20-5e9bbfa2fe50.png)

### Data
<ul>
  <li>This part is just useful to get the correct data stored in workspace or to visulize them in Data inspector.</li>
  <li>If you need to anylze some data, try to send them to workspace</li>
</ul>

### Scope
<ul>
  <li>This part is not necessary (it is commented). you can just use Data inspector instead of it.</li>
  <li>However, it is better than Data Inspector if your need to get better signal anlaysis.</li>
</ul>

## Workspace
To anylyse the different data we use some .mlx and .m files:
### start.mlx
This file is used to start different simulations with different strategies.</br>
:arrow_right:<b>USE THIS FILE TO START THE SIMULATION PROCESS</b>:arrow_left:
### Comparison.mlx
This file is used to compare the results of the different EMS:
<ul>
  <li>DC Bus Voltage Curves</li>
  <li>Load Power</li>
  <li>RMSE</li>
  <li>Mean Error</li>
  <li>SOC</li>
  <li>SOH</li>
  <li>...</li>
</ul>
