# pip install selenium
# Download the apt web driver from https://selenium-python.readthedocs.io/installation.html#drivers
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

# driver = webdriver.Chrome()

# Opens all these links in a separate tab in Firefox, it is not supportted for Chrome for yet, need to add some hacks
WEB_URLS = [
            'https://techcrunch.com/',
            'https://nvidia.sharepoint.com/sites/nvinfo',
            'https://news.google.com/?hl=en-US&gl=US&ceid=US:en',
            'https://timesofindia.indiatimes.com/',
            'https://www.xe.com/currencycharts/?from=USD&to=INR',
            'https://www.marketwatch.com/investing/stock/nvda',
            'https://www.marketwatch.com/investing/stock/amzn'
            ]

if __name__ == '__main__':
    # Allow new tab folder in Firefox 
    fp = webdriver.FirefoxProfile()
    fp.set_preference("browser.tabs.remote.autostart", False)
    fp.set_preference("browser.tabs.remote.autostart.1", False)
    fp.set_preference("browser.tabs.remote.autostart.2", False)

    caps = DesiredCapabilities().FIREFOX
    caps["pageLoadStrategy"] = "none" 

    driver = webdriver.Firefox(firefox_profile=fp, desired_capabilities=caps)

    for (tab, url) in enumerate(WEB_URLS, 1):
        driver.find_element_by_tag_name('body').send_keys(Keys.CONTROL + 't')
        windows = driver.window_handles
        driver.switch_to.window(windows[tab])
        driver.get(url)

# driver.find_element_by_xpath('//*[contains(text(), "Upload ETL")]').click()
# driver.find_element_by_id('etlFile').send_keys("C:\\Test.etl")
# driver.find_element_by_id('statsName').send_keys('Sample ETL')
# driver.find_element_by_id('uploader').send_keys('Varun')
# driver.find_element_by_id('uploadStats').click()
