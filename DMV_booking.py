from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import Select
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as ec
import sys
import time

LOCATIONS = ['SANTA CLARA', 'SAN JOSE', 'FREMONT', 'GILROY', 'HOLLISTER']
# driver = webdriver.Chrome()
driver = webdriver.Firefox()

def getLatestAppointment(Location):
	try:
		driver.get('https://www.dmv.ca.gov/wasapp/foa/clear.do?goTo=driveTest')
		driver.find_element_by_xpath('//*[@id="officeId"]').click()
		Select(driver.find_element_by_id('officeId')).select_by_visible_text(location)
		driver.find_element_by_id('DT').click()
		driver.find_element_by_id('first_name').send_keys('Dhananjay')
		driver.find_element_by_id('last_name').send_keys('Gowda Narasimha Murthy')
		driver.find_element_by_id('dl_number').send_keys('Y5618873')
		driver.find_element_by_id('birthMonth').send_keys('05')
		driver.find_element_by_id('birthDay').send_keys('17')
		driver.find_element_by_id('birthYear').send_keys('1992')
		driver.find_element_by_id('areaCode').send_keys('612')
		driver.find_element_by_id('telPrefix').send_keys('404')
		driver.find_element_by_id('telSuffix').send_keys('9487')
		driver.find_element_by_id('officeId2').send_keys('9487')
		driver.find_element_by_xpath('/html/body/div[2]/div[2]/form/fieldset/div[5]/input[2]').click()
		Appointment = None
		while Appointment is None: 
			Appointment = driver.find_element_by_xpath('/html/body/div[2]/div[2]/form[1]/div/div[2]/table/tbody/tr/td[2]/p[2]')
			print(Appointment.text)
			time.sleep(1)
		# driver.find_element_by_tag_name('body').send_keys(Keys.CONTROL + 'w')
		return Appointment.text
	except:
		pass

for location in LOCATIONS:
	appointment = getLatestAppointment(location)
	print('{} {} '.format(location, appointment))
	break
# driver.close()

sys.exit(0)
if 0:
    search = driver.find_element_by_name('searchText')
    print (search)
    search.clear()
    search.send_keys("varunvijayak")
    search.send_keys(Keys.RETURN)

driver.find_element_by_xpath('//*[contains(text(), "Upload ETL")]').click()
driver.find_element_by_id('etlFile').send_keys("C:\\sel\\Test.etl")
driver.find_element_by_id('statsName').send_keys('Sample ETL')
driver.find_element_by_id('uploader').send_keys('Varun')
driver.find_element_by_id('uploadStats').click()
