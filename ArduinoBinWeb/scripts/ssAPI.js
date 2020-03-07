// Gets most spreadsheet entry

const SHEET_ID = "1Qyy25yesqFlnQmXB5tJPd1JoPqWuW3Znv48zgeDISZI";
const ACCESS_TOKEN = "ya29.Il_BBxNF3tmnNXwcCeZp5QIHClCY7mmu6jeqM5UaYdu-O4WkmG9QOnEZgbdKkwKJQJRvl1qwLL2wMjr_QIzxwFplOY82FGIxfkRfIJ5sXM6Q6GrOPS7YfzuGOxoglIks2g";

let url = `https://sheets.googleapis.com/v4/spreadsheets/${SHEET_ID}/values/A2:D2`;

getSheetValues = async () => {
    try {
        await fetch(url,
            {
                headers: {
                    "Content-Type": "application/json",
                    Authorization: `Bearer ${ACCESS_TOKEN}`
                }
            })
            .then(resp => resp.json())
            .then((data) => {
                console.log(data);

                // Creates a new paragraph elemnt inside the div binStatus
                var parentElement = document.getElementById('binStatus');
                var statuspCreate = document.createElement('p');
                var statusp = parentElement.appendChild(statuspCreate);

                // Makes a var pointing to the values of the array returned from the fetch
                var vals = data.values[0];

                // If the 3rd and 4th elemnt of the values (half and full) are
                // Both 0, then the nin is full, if half is 0 then it is half full
                // If both are 1, then it is empty
                if (vals[2] == 0 && vals[3] == 0)
                {
                    statusp.innerHTML = "Your bin is completely full! Please empty it.";
                }
                else if (vals[2] == 0)
                {
                    statusp.innerHTML = "Your bin is half full. You will need to empty it soon";
                }
                else
                {
                    statusp.innerHTML = "Your bin is currently empty.";
                }
            })
     }
    catch(err)
    {
        console.error(err);
    }
}

getSheetValues();