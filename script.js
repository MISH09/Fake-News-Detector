function analyze() {
    let title = document.getElementById("title").value;
    let content = document.getElementById("content").value;
    let source = document.getElementById("source").value;

    let score = 50;
    let explanation = "";

    // Keyword Rule
    let keywords = ["shocking", "breaking", "secret"];
    let found = keywords.find(w => content.toLowerCase().includes(w));

    if (found) {
        score -= 20;
        explanation += `Keyword Rule: -20 (Found ${found})<br>`;
    } else {
        explanation += `Keyword Rule: 0<br>`;
    }

    // Source Rule
    let trusted = ["bbc.com", "reuters.com", "thehindu.com"];
    if (trusted.includes(source.toLowerCase())) {
        score += 30;
        explanation += `Source Rule: +30 (Trusted)<br>`;
    } else {
        score -= 30;
        explanation += `Source Rule: -30 (Untrusted)<br>`;
    }

    // Title Rule
    if (!content.toLowerCase().includes(title.split(" ")[0].toLowerCase())) {
        score -= 20;
        explanation += `Title Rule: -20 (Mismatch)<br>`;
    } else {
        score += 10;
        explanation += `Title Rule: +10 (Match)<br>`;
    }

    let result = "";
    if (score >= 80) result = "RELIABLE";
    else if (score >= 50) result = "SUSPICIOUS";
    else result = "FAKE NEWS";

    // Save
    let data = JSON.parse(localStorage.getItem("newsData")) || [];
    data.push({ title, content, source, score, result });
    localStorage.setItem("newsData", JSON.stringify(data));

    document.getElementById("result").innerHTML =
        `<b>Score:</b> ${score}<br><b>Result:</b> ${result}`;

    document.getElementById("explanation").innerHTML =
        `<h3>Explanation</h3>${explanation}`;
}

// View
function viewSaved() {
    let data = JSON.parse(localStorage.getItem("newsData")) || [];
    let output = "";

    data.forEach(item => {
        output += `
        <div class="card">
            <b>${item.title}</b><br>
            Score: ${item.score}<br>
            Result: ${item.result}
        </div>`;
    });

    document.getElementById("saved").innerHTML = output;
}

// Search
function searchArticle() {
    let keyword = document.getElementById("searchInput").value;
    let data = JSON.parse(localStorage.getItem("newsData")) || [];

    let output = "";
    let found = false;

    data.forEach(item => {
        if (
            item.title.toLowerCase().includes(keyword.toLowerCase()) ||
            item.content.toLowerCase().includes(keyword.toLowerCase())
        ) {
            found = true;
            output += `
            <div class="card">
                <b>${item.title}</b><br>
                Score: ${item.score}<br>
                Result: ${item.result}
            </div>`;
        }
    });

    if (!found) output = "No results found.";

    document.getElementById("saved").innerHTML = output;
}