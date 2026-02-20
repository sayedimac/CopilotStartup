import { test, expect, request } from '@playwright/test';

const API_BASE_URL = process.env.API_BASE_URL || 'http://localhost:7071';

// ─── API Tests ───────────────────────────────────────────────────────────────

test.describe('Chat API', () => {
  test('POST /api/chat returns a reply for a valid message', async () => {
    const context = await request.newContext({ baseURL: API_BASE_URL });

    const response = await context.post('/api/chat', {
      data: { message: 'Hello from Playwright' },
    });

    expect(response.status()).toBe(200);
    const body = await response.json();
    expect(body).toHaveProperty('reply');
    expect(body).toHaveProperty('conversationId');
    expect(body).toHaveProperty('timestamp');
    expect(typeof body.reply).toBe('string');
    expect(body.reply.length).toBeGreaterThan(0);
  });

  test('POST /api/chat preserves conversationId across turns', async () => {
    const context = await request.newContext({ baseURL: API_BASE_URL });

    const first = await context.post('/api/chat', {
      data: { message: 'First message' },
    });
    const firstBody = await first.json();
    const conversationId = firstBody.conversationId;

    const second = await context.post('/api/chat', {
      data: { message: 'Second message', conversationId },
    });
    const secondBody = await second.json();
    expect(secondBody.conversationId).toBe(conversationId);
  });

  test('POST /api/chat returns 400 for empty message', async () => {
    const context = await request.newContext({ baseURL: API_BASE_URL });

    const response = await context.post('/api/chat', {
      data: { message: '' },
    });

    expect(response.status()).toBe(400);
  });

  test('POST /api/chat returns 400 for missing body fields', async () => {
    const context = await request.newContext({ baseURL: API_BASE_URL });

    const response = await context.post('/api/chat', {
      data: {},
    });

    expect(response.status()).toBe(400);
  });
});

// ─── UI Tests ────────────────────────────────────────────────────────────────

test.describe('Chatbot UI', () => {
  test('loads the chat page with input and send button', async ({ page }) => {
    await page.goto('/');
    await expect(page.getByRole('heading', { name: /copilot chat/i })).toBeVisible();
    await expect(page.getByLabel('Message input')).toBeVisible();
    await expect(page.getByLabel('Send message')).toBeVisible();
  });

  test('send button is disabled when input is empty', async ({ page }) => {
    await page.goto('/');
    const sendBtn = page.getByLabel('Send message');
    await expect(sendBtn).toBeDisabled();
  });

  test('send button is enabled when input has text', async ({ page }) => {
    await page.goto('/');
    await page.getByLabel('Message input').fill('Hello');
    await expect(page.getByLabel('Send message')).toBeEnabled();
  });

  test('pressing Enter sends a message', async ({ page }) => {
    await page.goto('/');
    await page.getByLabel('Message input').fill('Hello');
    await page.getByLabel('Message input').press('Enter');
    await expect(page.locator('.chat-message.user .chat-bubble').first()).toContainText('Hello');
  });

  test('user message appears in the chat after sending', async ({ page }) => {
    await page.goto('/');
    const input = page.getByLabel('Message input');
    await input.fill('Test message');
    await page.getByLabel('Send message').click();
    await expect(page.locator('.chat-message.user .chat-bubble').first()).toContainText('Test message');
  });
});
