<<<<<<< HEAD
# Module: spccmd.py
# This is a Speech command module

import subprocess


def spccmd_welcome(): return "welcome to Recycling World."
def spccmd_greet_user(): return "Your ID is identified"
def spccmd_redlight_on(): return "Please throw it away to the Red Bin."
def spccmd_redlight_off(): return
def spccmd_bluelight_on(): return "Please throw it away to the Blue Bin."
def spccmd_bluelight_off(): return
def spccmd_greenlight_on(): return "Please throw it away to the Green Bin."
def spccmd_greenlight_off(): return
def spccmd_bye(): return "Bye."


def spk_out(incmd):
   p = subprocess.Popen(incmd, stdout=subprocess.PIPE, shell=True)
   (output, err) = p.communicate()
   return output

def cmd_check(intext):
	text = ""
	if (intext == "spccmd_welcome"):
		text = spccmd_welcome()
	elif (intext == "spccmd_greet_user"):
		text = spccmd_greet_user()
	elif (intext == "spccmd_redlight_on"):
		text = spccmd_redlight_on()
	elif (intext == "spccmd_redlight_off"):
		text = spccmd_redlight_off()
	elif (intext == "spccmd_bluelight_on"):
		text = spccmd_bluelight_on()
	elif (intext == "spccmd_bluelight_off"):
		text = spccmd_bluelight_off()
	elif (intext == "spccmd_greenlight_on"):
		text = spccmd_greenlight_on()
	elif (intext == "spccmd_greenlight_off"):
		text = spccmd_greenlight_off()
	elif (intext == "spccmd_bye"):
		text = spccmd_bye()
	
	return text


########################################################
# How to Use ###########################################
########################################################
# please look below	
########################################################
# a = "Some amazing words of wisdom."
in_text = "spccmd_greenlight_on"
text = cmd_check(in_text)

# write out to wav file
spker0 = 'espeak -w temp.wav "%s" 2>>/dev/null' % text

# speak aloud
spker1 = 'espeak -ven+f3 -k5 -s150 --punct="<characters>" "%s" 2>>/dev/null' % text #speak aloud

print text

# Call by
spk_out(spker0)
spk_out(spker1)
=======
# Module: spccmd.py
# This is a Speech command module

import subprocess


def spccmd_welcome(): return "welcome to Recycling World."
def spccmd_greet_user(): return "Your ID is identified"
def spccmd_redlight_on(): return "Please throw it away to the Red Bin."
def spccmd_redlight_off(): return
def spccmd_bluelight_on(): return "Please throw it away to the Blue Bin."
def spccmd_bluelight_off(): return
def spccmd_greenlight_on(): return "Please throw it away to the Green Bin."
def spccmd_greenlight_off(): return
def spccmd_bye(): return "Bye."


def spk_out(incmd):
   p = subprocess.Popen(incmd, stdout=subprocess.PIPE, shell=True)
   (output, err) = p.communicate()
   return output

def cmd_check(intext):
	text = ""
	if (intext == "spccmd_welcome"):
		text = spccmd_welcome()
	elif (intext == "spccmd_greet_user"):
		text = spccmd_greet_user()
	elif (intext == "spccmd_redlight_on"):
		text = spccmd_redlight_on()
	elif (intext == "spccmd_redlight_off"):
		text = spccmd_redlight_off()
	elif (intext == "spccmd_bluelight_on"):
		text = spccmd_bluelight_on()
	elif (intext == "spccmd_bluelight_off"):
		text = spccmd_bluelight_off()
	elif (intext == "spccmd_greenlight_on"):
		text = spccmd_greenlight_on()
	elif (intext == "spccmd_greenlight_off"):
		text = spccmd_greenlight_off()
	elif (intext == "spccmd_bye"):
		text = spccmd_bye()
	
	return text


########################################################
# How to Use ###########################################
########################################################
# please look below	
########################################################
# a = "Some amazing words of wisdom."
in_text = "spccmd_greenlight_on"
text = cmd_check(in_text)

# write out to wav file
spker0 = 'espeak -w temp.wav "%s" 2>>/dev/null' % text

# speak aloud
spker1 = 'espeak -ven+f3 -k5 -s150 --punct="<characters>" "%s" 2>>/dev/null' % text #speak aloud

print text

# Call by
spk_out(spker0)
spk_out(spker1)
>>>>>>> a17139e1560a1197baebb82530201dd258429a6c
