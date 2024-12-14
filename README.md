# Gaming Script Interpreter Documentation

## Welcome to **Clash and Conquest**
This is a simple command-based interpreter designed to simulate a stats-based fighting game. You can create champion stats, perform battle actions, and view updated game stats in real-time.

---

## **Available Commands**
Here is a list of commands you can use to interact with the game:

### 1. **Create Command**
**Syntax:**
```plaintext
create <stat_name> <value>
```

**Description:**
This command creates a new stat (e.g., `health`, `attackdamage`, `armor`) with a specified value.

**Example:**
```plaintext
create health 200
create attackdamage 50
```
**Effect:**
Creates a `health` stat with a value of `200` and an `attackdamage` stat with a value of `50`.

---

### 2. **Attack Command**
**Syntax:**
```plaintext
attack <stat1> <stat2> <result_stat>
```

**Description:**
Adds two stats together (e.g., `attackdamage` and `bonusattack`) to calculate a new stat representing the total offensive power.

**Example:**
```plaintext
attack attackdamage bonusattack totalattackdamage
```
**Effect:**
Calculates the sum of `attackdamage` and `bonusattack` and stores the result in `totalattackdamage`.

---

### 3. **Defend Command**
**Syntax:**
```plaintext
defend <stat1> <stat2> <damage_taken_stat> <remaining_health_stat>
```

**Description:**
Subtracts one stat (e.g., damage mitigation through `armor`) from another stat (e.g., `totalattackdamage`) to calculate the remaining health after damage.

**Example:**
```plaintext
defend totalattackdamage armor damagetaken remaininghealth
```
**Effect:**
- Calculates `damagetaken` as `totalattackdamage - armor` (with a minimum of 0).
- Calculates `remaininghealth` as `health - damagetaken`.

---

### 4. **Print Command**
**Syntax:**
```plaintext
print <stat_name>
```

**Description:**
Displays the current value of the specified stat.

**Example:**
```plaintext
print totalattackdamage
```
**Effect:**
Displays the value of `totalattackdamage` in the console.

---

## **Attributes to Choose From**
You can define the following attributes to simulate game scenarios:
- **health:** Represents the champion's total health.
- **attackdamage:** Represents the base attack damage.
- **bonusattack:** Additional damage from buffs or items.
- **armor:** Reduces damage taken.
- **damagetaken:** Damage received during combat.
- **remaininghealth:** Health remaining after taking damage.

---

## **Example Gameplay**
Below is an example input and output to demonstrate the functionality of the interpreter.

### **Input Script:**
```plaintext
create health 200
create attackdamage 50
create bonusattack 25
create armor 30
attack attackdamage bonusattack totalattackdamage
defend totalattackdamage armor damagetaken remaininghealth
print damagetaken
print remaininghealth
```

### **Output:**
```plaintext
Command: create - Created stat 'health' with value 200
Command: create - Created stat 'attackdamage' with value 50
Command: create - Created stat 'bonusattack' with value 25
Command: create - Created stat 'armor' with value 30
Command: attack - Calculated 'totalattackdamage' as sum of attackdamage and bonusattack = 75
Command: defend - Damage Taken = 75 (Total Attack Damage) - 30 (Armor) = 45
Remaining Health = 200 (Initial Health) - 45 (Damage Taken) = 155
Command: print - damagetaken = 45
Command: print - remaininghealth = 155
```

---

## **How to Start**
1. Run the program in your terminal.
2. Enter commands to define stats and perform actions.
3. Use the `print` command to view specific stats.
4. Press ENTER on an empty line to execute your script.

Enjoy creating your own champion and exploring battle scenarios!
