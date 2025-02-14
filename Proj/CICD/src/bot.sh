#!/bin/bash
ID="728732700" 
TOKEN="7229695625:AAEaaVkAlqeQgGvIUmJ1CwOcVdzl4lOUb90"
URL="https://api.telegram.org/bot$TOKEN/sendMessage"
MESSAGE="$CI_PROJECT_NAME %0A $CI_JOB_NAME %0A  $CI_JOB_STATUS %0A"
curl -s --max-time 10 -d "chat_id=$ID&disable_web_page_preview=1&text=$MESSAGE" $URL > /dev/null
